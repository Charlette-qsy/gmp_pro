//ʱ��߶�Ԥ����ָ��
`timescale 1ns / 1ps

//ģ������spi_send_tb
module spi_send_tb();

logic spi_clk;//SPIʱ��
logic spi_csn;//SPIƬѡ
logic spi_sdi;//SPI����

//����50MHzʱ�Ӽ���
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

//���һ��SPIʱ���Σ��������
initial begin
  #2000
  $finish;
end

//����spi_sendģ��
spi_send spi_send(
  .sys_clk     (sys_clk     ),
  .sys_reset   (sys_reset   ),
  .i_data      (16'haa11    ),
  .i_data_en   (1'b1        ),
  .spi_clk     (spi_clk     ),
  .spi_csn     (spi_csn     ),
  .spi_sdi     (spi_sdi     )); 

endmodule
