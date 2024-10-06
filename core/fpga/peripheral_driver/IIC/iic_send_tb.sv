//ʱ��߶�Ԥ����ָ��
`timescale 1ns / 1ps

//ģ������iic_send_tb
module iic_send_tb();

logic iic_send_scl;//IICʱ��
wire iic_send_sda;//IIC����

//����ʱ�Ӽ���
bit sys_clk;
initial begin
  sys_clk = 0;
  forever
  #10 sys_clk = !sys_clk;
end

//������λ����
bit sys_reset;
initial begin
  sys_reset = 1;
  #1000
  sys_reset = 0;
end

//����iic_sendģ��
iic_send iic_send(
  .sys_clk         (sys_clk       ),
  .sys_reset       (sys_reset     ),
  .iic_send_en     (1'b1          ),
  .iic_device_addr (7'b1010_111   ),
  .iic_send_addr   (8'h01         ),
  .iic_send_data   (8'haa         ),
  .iic_scl         (iic_send_scl  ) ,
  .iic_sda         (iic_send_sda  ));

endmodule
