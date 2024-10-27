//ʱ��߶�Ԥ����ָ��
`timescale 1ns / 1ps

//ģ������iic_send
module iic_send(
input       sys_clk         ,//ϵͳʱ�ӣ�Ƶ��Ϊ200KHz
input       sys_reset       ,//ϵͳ��λ���ߵ�ƽ��Ч
input       iic_send_en     ,//�û�дʹ��
input [6:0] iic_device_addr ,//���豸������ַ
input [7:0] iic_send_addr   ,//I�û��Ĵ�����ַ
input [7:0] iic_send_data   ,//I�û��Ĵ�������
output      iic_scl         ,//IICʱ�ӣ�200KHz
inout       iic_sda        );//IIC����

parameter  idle              = 8'h01;//��״̬
parameter  send_device_state = 8'h02;//����������ַ״̬
parameter  send_addr_state   = 8'h04;//�����û���ַ״̬
parameter  send_data_state   = 8'h08;//�����û�����״̬
parameter  send_end_state    = 8'h10;//���ͽ���״̬
parameter  send_ack1_state   = 8'h20;//����������ַӦ��״̬
parameter  send_ack2_state   = 8'h40;//�����û���ַӦ��״̬
parameter  send_ack3_state   = 8'h80;//�����û�����Ӧ��״̬

reg  [7:0]  iic_cstate               ;//��ǰ״̬
reg  [7:0]  iic_nstate               ;//��һ״̬
reg  [3:0]  send_device_cnt          ;//����������ַ״̬������
reg  [3:0]  send_addr_cnt            ;//�����û���ַ״̬������
reg  [3:0]  send_data_cnt            ;//�������ݵ�ַ״̬������
reg         iic_ack_en               ;//Ӧ���ź�ʹ��
wire        iic_ack                  ;//Ӧ���ź�
reg         sda_reg                  ;//IICʱ��
reg         scl_reg                  ;//IIC����

//assign iic_ack = iic_sda              ;//ʵ��
assign iic_ack = 1'b0                 ;//����

//��ǰ״̬��ת
always @(posedge sys_clk)begin
  if(sys_reset)
    iic_cstate <= idle;
  else
    iic_cstate <= iic_nstate;
end

//��һ״̬��ת
always @(*)begin
  //״̬����ʼ��
  iic_nstate = idle;
  case(iic_cstate)
  idle:begin
    //�û�д����ʹ�ܣ���ת������������ַ״̬
    if(iic_send_en)
      iic_nstate = send_device_state;
    else
      iic_nstate = idle;    
  end
  send_device_state:begin
    //����������ַ��ɣ���ת��������ַӦ��״̬
    if(send_device_cnt == 'd8)
      iic_nstate = send_ack1_state;
    else
      iic_nstate = send_device_state;
  end
  send_addr_state:begin
    //�����û���ַ��ɣ���ת���û���ַӦ��״̬
    if(send_addr_cnt == 'd8)
      iic_nstate = send_ack2_state;
    else
      iic_nstate = send_addr_state;
  end
  send_data_state:begin
    //�����û�������ɣ���ת���û�����Ӧ��״̬
    if(send_data_cnt == 'd8)
      iic_nstate = send_ack3_state;
    else
      iic_nstate = send_data_state;
  end
  send_ack1_state:begin
    if(!iic_ack)//Ӧ����Ӧ
      iic_nstate = send_addr_state;
    else
      iic_nstate = send_ack1_state;
  end
  send_ack2_state:begin
    if(!iic_ack)//Ӧ����Ӧ
      iic_nstate = send_data_state;
    else
      iic_nstate = send_ack2_state;
  end
   send_ack3_state:begin
    if(!iic_ack)//Ӧ����Ӧ
      iic_nstate = send_end_state;
    else
      iic_nstate = send_ack3_state;
  end
  send_end_state:begin
    iic_nstate = idle;//д���ݽ���
  end
  default:begin
    //��ֹ״̬���ܷɣ����»ص���״̬
    iic_nstate = idle;
  end
  endcase
end

//����������ַ״̬ʱ������������������״̬������������
always @(posedge sys_clk)begin
  if(sys_reset)
    send_device_cnt <= 'd0;
  else if(iic_cstate == send_device_state)
    send_device_cnt <= send_device_cnt + 'd1;
  else
    send_device_cnt <= 'd0;
end

//�����û���ַ״̬ʱ������������������״̬������������
always @(posedge sys_clk)begin
  if(sys_reset)
    send_addr_cnt <= 'd0;
  else if(iic_cstate == send_addr_state)
    send_addr_cnt <= send_addr_cnt + 'd1;
  else
    send_addr_cnt <= 'd0;
end

//�����û�����״̬ʱ������������������״̬������������
always @(posedge sys_clk)begin
  if(sys_reset)
    send_data_cnt <= 'd0;
  else if(iic_cstate == send_data_state)
    send_data_cnt <= send_data_cnt + 'd1;
  else
    send_data_cnt <= 'd0;
end

always @(posedge sys_clk)begin
  if(sys_reset)
    iic_ack_en <= 'd0;
  else if(iic_cstate == send_device_state)begin
    if(send_device_cnt == 'd8)//������ַ�����꣬�ȴ�Ӧ��
      iic_ack_en <= 'd1;
    else
      iic_ack_en <= 'd0;
  end
  else if(iic_cstate == send_addr_state)begin
    if(send_addr_cnt == 'd8)//�û���ַ�����꣬�ȴ�Ӧ��
      iic_ack_en <= 'd1;
    else
      iic_ack_en <= 'd0;
  end    
  else if(iic_cstate == send_data_state)begin
    if(send_data_cnt == 'd8)//�û����ݷ����꣬�ȴ�Ӧ��
      iic_ack_en <= 'd1;
    else
      iic_ack_en <= 'd0;
  end  
  else
    iic_ack_en <= 'd0;
end

//���IIC����
always @(posedge sys_clk)begin
  if(sys_reset)
    sda_reg <= 'd1;
  else if(iic_cstate == idle && iic_nstate == send_device_state)
    sda_reg <= 'd0;//IIC��ʼʱ��
  else if(iic_cstate == send_device_state)begin
     case(send_device_cnt)//����������ַ���ȷ��͸�λ���ٷ��͵�λ
       'd0:sda_reg <= iic_device_addr[6];
       'd1:sda_reg <= iic_device_addr[5];
       'd2:sda_reg <= iic_device_addr[4];
       'd3:sda_reg <= iic_device_addr[3];
       'd4:sda_reg <= iic_device_addr[2];
       'd5:sda_reg <= iic_device_addr[1];
       'd6:sda_reg <= iic_device_addr[0];
       'd7:sda_reg <= 'd0               ;//0����д����
     endcase
  end
  else if(iic_cstate == send_addr_state)begin
     case(send_addr_cnt)//�����û���ַ���ȷ��͸�λ���ٷ��͵�λ
       'd0:sda_reg <= iic_send_addr[7];
       'd1:sda_reg <= iic_send_addr[6];
       'd2:sda_reg <= iic_send_addr[5];
       'd3:sda_reg <= iic_send_addr[4];
       'd4:sda_reg <= iic_send_addr[3];
       'd5:sda_reg <= iic_send_addr[2];
       'd6:sda_reg <= iic_send_addr[1];
       'd7:sda_reg <= iic_send_addr[0];
     endcase
  end    
  else if(iic_cstate == send_data_state)begin
     case(send_data_cnt)//�����û����ݣ��ȷ��͸�λ���ٷ��͵�λ
       'd0:sda_reg <= iic_send_data[7];
       'd1:sda_reg <= iic_send_data[6];
       'd2:sda_reg <= iic_send_data[5];
       'd3:sda_reg <= iic_send_data[4];
       'd4:sda_reg <= iic_send_data[3];
       'd5:sda_reg <= iic_send_data[2];
       'd6:sda_reg <= iic_send_data[1];
       'd7:sda_reg <= iic_send_data[0];
     endcase
  end
  else if(iic_cstate == send_end_state)
    sda_reg <= 'd1;
end

//���IICʱ��
always @(*)begin
  scl_reg = 1'b1;
  //����������ַʱ�����IICʱ��
  if(iic_cstate == send_device_state)
    scl_reg = sys_clk;
  //�����û���ַʱ�����IICʱ��
  else if(iic_cstate == send_addr_state)begin
    if(send_addr_cnt == 'd0)
      scl_reg = 1'b1;
    else
      scl_reg = sys_clk;
  end
  //�����û�����ʱ�����IICʱ��
  else if(iic_cstate == send_data_state)begin
    if(send_data_cnt == 'd0)
      scl_reg = 1'b1;
    else
      scl_reg = sys_clk;
  end
  else 
    scl_reg = 1'b1;
end

assign iic_scl =  scl_reg;
assign iic_sda = (iic_ack_en)?1'bz:sda_reg;

endmodule
