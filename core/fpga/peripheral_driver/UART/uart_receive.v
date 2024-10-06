//ʱ��߶�Ԥ����ָ��
`timescale 1ns / 1ps

//ģ������uart_receive
module uart_receive(
input            sys_clk            ,//ϵͳʱ�ӣ������ʶ�Ӧʱ��
input            sys_reset          ,//ϵͳ��λ���ߵ�ƽ��Ч
input            uart_rx            ,//UART���գ�1bit
output reg[7:0] o_receive_data     ,//�û���������
output reg      o_receive_data_en  );//�û�����������Ч

reg         receive_count_en =0 ;//����ʹ��
reg   [3:0] receive_count    =0 ;//���ռ�����

//���տ�ʼ�����߽���ʹ�ܣ����ս��������ͽ���ʹ��
always @(posedge sys_clk)begin
  if(sys_reset)
    receive_count_en <= 'd0;
  else if(receive_count == 'd8)
    receive_count_en <= 'd0;
  else if(!uart_rx)
    receive_count_en <= 'd1;
end

//����ʹ��Ϊ1ʱ������������������״̬�����������
always @(posedge sys_clk)begin
  if(sys_reset)
    receive_count <= 'd0;
  else if(receive_count_en)
    receive_count <= receive_count +'d1;
  else 
    receive_count <= 'd0;
end

//����ת������UART��������ת��Ϊ�����������
always @(posedge sys_clk)begin
  if(sys_reset)
    o_receive_data <= 'd0;
  else if(receive_count_en)begin
    case(receive_count)
    'd0:o_receive_data[0] <= uart_rx;//���յ�1bit
    'd1:o_receive_data[1] <= uart_rx;//���յ�2bit
    'd2:o_receive_data[2] <= uart_rx;//���յ�3bit
    'd3:o_receive_data[3] <= uart_rx;//���յ�4bit
    'd4:o_receive_data[4] <= uart_rx;//���յ�5bit
    'd5:o_receive_data[5] <= uart_rx;//���յ�6bit
    'd6:o_receive_data[6] <= uart_rx;//���յ�7bit
    'd7:o_receive_data[7] <= uart_rx;//���յ�8bit
    endcase
  end
end

//�����������ʱ���������ʹ���ź�
always @(posedge sys_clk)begin
  if(sys_reset)
    o_receive_data_en <= 'd0;
  else if(receive_count_en)begin
    if(receive_count == 'd8)
      o_receive_data_en <= 'd1;
    else
      o_receive_data_en <= 'd0;
  end
  else 
    o_receive_data_en <= 'd0;
end

endmodule
