//ʱ��߶�Ԥ����ָ��
`timescale 1ns / 1ps

//ģ������uart_send
module uart_send(
input       sys_clk          ,//ϵͳʱ�ӣ������ʶ�Ӧʱ��
input       sys_reset        ,//ϵͳ��λ���ߵ�ƽ��Ч
input [7:0] i_send_data      ,//�û���������
input       i_send_data_en   ,//�û�����������Ч
output reg  uart_tx          ,//UART���ͣ�1bit
output reg  uart_busy       );//UART����æ��1æ��0��

reg   [7:0] data_reg1       =0;//���Ͳ�������
reg         send_enable     =0;//����ʹ��
reg   [3:0] send_enable_cnt =0;//���ͼ�����

//�Ĵ淢������
always @(posedge sys_clk)begin
  if(sys_reset)
    data_reg1 <= 'd0;
  else if(i_send_data_en)
    data_reg1 <= i_send_data;
end

//���Ϳ�ʼ�����߷���ʹ�ܣ����ͽ��������ͷ���ʹ��
always @(posedge sys_clk)begin
  if(sys_reset)
    send_enable <= 'd0;
  else if(send_enable_cnt == 'd9)
    send_enable <= 'd0;
  else if(i_send_data_en)
    send_enable <= 'd1;
end

//����ʹ��Ϊ1������������������״̬�����������
always @(posedge sys_clk)begin
  if(sys_reset)
    send_enable_cnt <= 'd0;
  else if(send_enable)
    send_enable_cnt <= send_enable_cnt + 'd1;
  else 
    send_enable_cnt <= 'd0;
end

//����ת�������û���������ת��Ϊ�����������
always @(posedge sys_clk)begin
  if(sys_reset)
    uart_tx <= 'd1;
  else if(send_enable)begin
    case(send_enable_cnt)
          'd0:uart_tx <= 'd0         ;//���Ϳ�ʼ
          'd1:uart_tx <= data_reg1[0];//���͵�1bit
          'd2:uart_tx <= data_reg1[1];//���͵�2bit
          'd3:uart_tx <= data_reg1[2];//���͵�3bit
          'd4:uart_tx <= data_reg1[3];//���͵�4bit
          'd5:uart_tx <= data_reg1[4];//���͵�5bit
          'd6:uart_tx <= data_reg1[5];//���͵�6bit
          'd7:uart_tx <= data_reg1[6];//���͵�7bit
          'd8:uart_tx <= data_reg1[7];//���͵�8bit
          'd9:uart_tx <= 'd1         ;//���ͽ���
      default:uart_tx <= 'd1;
    endcase
  end
end

//������ʱ������æ״̬������������ʱ��������״̬
always @( * )begin
  if(sys_reset)
    uart_busy = 'd0;
  else if(i_send_data_en == 1'b1)
    uart_busy = 'd1;
  else if(send_enable == 1'b1)
    uart_busy = 'd1;
  else if(send_enable_cnt == 'd10)
    uart_busy = 'd1;
  else
    uart_busy = 'd0;
end

endmodule
