//ʱ��߶�Ԥ����ָ��
`timescale 1ns / 1ps

//ģ������can_send_tb
module can_send_tb();
logic [7:0] o_can_addr      ;//�û������ݵ�ַ
logic [7:0] o_can_data      ;//�û�������
logic       o_can_data_valid;//�û���������Ч
logic       can_ale         ;//CAN�ӿ�
logic       can_cs          ;//CAN�ӿ�
logic       can_rd          ;//CAN�ӿ�
logic       can_wr          ;//CAN�ӿ�
wire [7:0] can_ad          ;//CAN�ӿ�

//����ʱ�Ӽ���
bit sys_clk;
initial begin
  sys_clk = 0;
  forever
  #100 sys_clk = !sys_clk;
end

//������λ����
bit sys_reset;
initial begin
  sys_reset = 1;
  #1000
  sys_reset = 0;
end

//���������
byte  sim_count;
always @(posedge sys_clk)begin
  if(sys_reset)
    sim_count <= 'd0;
  else if(sim_count == 'd200)
    sim_count <= 'd200;
  else
    sim_count <= sim_count + 'd1;
end

//����CAN��д����
logic  [1:0] i_can_wr_sel     = 2'b00;
logic        i_can_data_valid = 0    ;
always @(posedge sys_clk)begin
  if(sys_reset)begin
    i_can_wr_sel     <= 2'b00;
    i_can_data_valid <= 'd0;
  end
  else if(sim_count == 'd50)begin//дָ��
    i_can_wr_sel     <= 2'b01;
    i_can_data_valid <= 'd1;
  end
  else if(sim_count == 'd100)begin//��ָ��
    i_can_wr_sel     <= 2'b10;
    i_can_data_valid <= 'd1;
  end
  else begin
    i_can_wr_sel     <= i_can_wr_sel;
    i_can_data_valid <= 'd0;
  end
end

//����can_sendģ��
can_send can_send(
  .sys_clk         (sys_clk         ),
  .sys_reset       (sys_reset       ),
  .i_can_wr_sel    (i_can_wr_sel    ),
  .i_can_wr_addr   (8'h01           ),
  .i_can_data      (8'h5a           ),
  .i_can_data_valid(i_can_data_valid),
  .o_can_addr      (o_can_addr      ),
  .o_can_data      (o_can_data      ),
  .o_can_data_valid(o_can_data_valid),
  .can_ale         (can_ale         ),
  .can_cs          (can_cs          ),
  .can_rd          (can_rd          ),
  .can_wr          (can_wr          ),
  .can_ad          (can_ad          ));

endmodule
