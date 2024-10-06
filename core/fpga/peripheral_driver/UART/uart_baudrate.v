//ʱ��߶�Ԥ����ָ��
`timescale 1ns / 1ps

//ģ������uart_baud_rate
module uart_baud_rate(
input        sys_clk           ,//ϵͳʱ�ӣ�Ƶ��Ϊ50MHz
input        sys_reset         ,//ϵͳ��λ���ߵ�ƽ��Ч
input [31:0] i_uart_bps        ,//����������
output reg   o_uart_clk       );//�����ʶ�Ӧʱ��

wire [15:0] bps_max_count;//������������ֵ
reg  [15:0] clk_count    ;//�����ʼ�����

assign bps_max_count =  50_000_000/i_uart_bps;

//�������������ֵʱ�����������
always @(posedge sys_clk)begin
  if(sys_reset)
    clk_count <= 'd0;
  else if(clk_count == bps_max_count)
    clk_count <= 'd0;
  else
    clk_count <= clk_count + 'd1;
end

//�����ʶ�Ӧʱ�����
always @(posedge sys_clk)begin
  if(sys_reset)
    o_uart_clk <= 'd0;
  else if(clk_count == bps_max_count)//���㲨����ʱ��ʱ��ʱ��ȡ��
    o_uart_clk <= ~o_uart_clk;
  else
    o_uart_clk <= o_uart_clk;
end

endmodule
