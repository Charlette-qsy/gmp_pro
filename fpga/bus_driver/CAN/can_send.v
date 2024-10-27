//ʱ��߶�Ԥ����ָ��
`timescale 1ns / 1ps

//ģ������can_send
module can_send(
input            sys_clk         , //ϵͳʱ�ӣ�Ƶ��Ϊ5MHz
input            sys_reset       , //ϵͳ��λ���ߵ�ƽ��Ч
input      [1:0] i_can_wr_sel    , //�û���д���01д��10��
input      [7:0] i_can_wr_addr   , //�û���д��ַ
input      [7:0] i_can_data      , //�û�д����
input            i_can_data_valid, //�û�д����
output reg[7:0] o_can_addr      , //�û�����ַ
output reg[7:0] o_can_data      , //�û�������
output reg      o_can_data_valid, //�û���������Ч
output reg      can_ale         , //CAN�ӿ�����
output reg      can_cs          , //CAN�ӿ�Ƭѡ
output reg      can_rd          , //CAN�ӿڶ�ʹ��
output reg      can_wr          , //CAN�ӿ�дʹ��
inout wire [7:0]can_ad          );//CAN�ӿ�����

parameter  can_idle        = 8'h01;//��״̬
parameter  can_write_state = 8'h02;//д����״̬
parameter  can_read_state  = 8'h04;//������״̬
parameter  can_end_state   = 8'h08;//����״̬

reg  [7:0]  can_cstate       ;//��ǰ״̬
reg  [7:0]  can_nstate       ;//��һ״̬
reg  [7:0]  write_cnt        ;//д������
reg  [7:0]  read_cnt         ;//��������
wire [7:0]  can_ad_rx        ;//�����ݱ���
reg  [7:0]  can_ad_reg1      ;//д���ݱ���

//��ǰ״̬��ת
always @(posedge sys_clk)begin
  if(sys_reset)
    can_cstate <= can_idle;
  else 
    can_cstate <= can_nstate;
end

//��һ״̬��ת
always @( * )begin
  can_nstate = can_idle;
  case(can_cstate)
    can_idle:begin
      if(i_can_data_valid)begin
        //дʹ�ܣ���ת��д״̬
        if(i_can_wr_sel == 2'b01)
          can_nstate = can_write_state;
        //��ʹ�ܣ���ת����״̬
        else if(i_can_wr_sel == 2'b10)
          can_nstate = can_read_state;
        else
          can_nstate = can_idle;
      end
      else 
        can_nstate = can_idle;
    end
    can_write_state:begin
      //д������ɣ���ת������״̬
      if(write_cnt == 'd5)
        can_nstate = can_end_state;
      else
        can_nstate = can_write_state;
    end
    can_read_state:begin
      //��������ɣ���ת������״̬
      if(read_cnt == 'd5)
        can_nstate = can_end_state;
      else
        can_nstate = can_read_state;
    end
    can_end_state:begin
      //��������ת����״̬
      can_nstate = can_idle;
    end
    default:begin
      //��������ת����״̬
      can_nstate = can_idle;
    end
  endcase
end

//д����״̬��д����������������״̬��д����������
always @(posedge sys_clk)begin
  if(sys_reset)
    write_cnt <= 'd0;
  else if(can_cstate == can_write_state)begin
    write_cnt <= write_cnt + 'd1;;
  end
  else 
    write_cnt <= 'd0;
end

//������״̬��������������������״̬��������������
always @(posedge sys_clk)begin
  if(sys_reset)
    read_cnt <= 'd0;
  else if(can_cstate == can_read_state)
    read_cnt <=  read_cnt + 'd1;
  else
    read_cnt <= 'd0; 
end

//CAN�ӿ����ʱ�����
always @(posedge sys_clk)begin
  if(sys_reset)begin
    can_ale     <= 'd0;
    can_cs      <= 'd1;
    can_rd      <= 'd1;
    can_wr      <= 'd1;
    can_ad_reg1 <= 'd0;
  end
  //д���ݿ���CAN�ӿ�Ϊдʱ��
  else if(can_cstate == can_write_state)begin
    case(write_cnt)
    'd0:begin
      can_ale     <= 'd1;
      can_ad_reg1 <= i_can_wr_addr;
    end
    'd1:begin
      can_ale     <= 'd1;
    end
    'd2:begin
      can_ale     <= 'd0;
      can_cs      <= 'd0;
    end
    'd3:begin
      can_wr      <= 'd0;
      can_ad_reg1 <= i_can_data;
    end
    'd4:begin
      can_wr      <= 'd1;
    end
    'd5:begin
      can_cs      <= 'd1;
    end
    endcase
  end
  //�����ݿ���CAN�ӿ�Ϊ��ʱ��
  else if(can_cstate == can_read_state)begin
    case(read_cnt)
    'd0:begin
      can_ale     <= 'd1;
      can_ad_reg1 <= i_can_wr_addr;
    end
    'd1:begin
      can_ale     <= 'd1;
    end
    'd2:begin
      can_ale     <= 'd0;
      can_cs      <= 'd0;
    end
    'd3:begin
      can_rd      <= 'd0;
      can_ad_reg1 <= 'dz;
    end
    'd4:begin
      can_rd      <= 'd1;
      can_ad_reg1 <= 'dz;
    end
    'd5:begin
      can_cs      <= 'd1;
      can_ad_reg1 <= 'd0;
    end
    endcase
  end
  else begin
    can_ale     <= 'd0;
    can_cs      <= 'd1;
    can_rd      <= 'd1;
    can_wr      <= 'd1;
    can_ad_reg1 <= 'd0;
  end
end

assign   can_ad_rx = (read_cnt == 'd4)?8'h5a:8'h00; //����ʹ��
//assign   can_ad_rx = (read_cnt == 'd4)?can_ad:8'h00;//ʵ��ʹ��

//д����ʱ�����д���ݣ�������ʱ���������̬
assign   can_ad   =  (read_cnt == 'd4)? 'dz:can_ad_reg1;

//�����Ĵ����
always @(posedge sys_clk)begin
  if(sys_reset)begin
    o_can_addr       <= 'd0;
    o_can_data       <= 'd0;
    o_can_data_valid <= 'd0;
  end
  else if(can_cstate == can_read_state)begin
    if(read_cnt == 'd4)begin
      o_can_addr       <= i_can_wr_addr;
      o_can_data       <= can_ad_rx;
      o_can_data_valid <= 'd1;
    end
    else begin
      o_can_addr       <= o_can_addr;
      o_can_data       <= o_can_data;
      o_can_data_valid <= 'd0;      
    end 
  end
end

endmodule