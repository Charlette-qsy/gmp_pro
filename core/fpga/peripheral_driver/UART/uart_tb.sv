//ʱ��߶�Ԥ����ָ��
`timescale 1ns / 1ps

//ģ������uart_tb
module uart_tb();
logic       o_uart_clk       ;//�û�ʱ�ӣ�������Ϊ115200
int         sim_count     = 0;//���������
logic [7:0] i_send_data   = 0;//�û���������
logic       i_send_data_en= 0;//�û�����������Ч
logic [7:0] o_receive_data   ;//�û���������
logic       o_receive_data_en;//�û�����������Ч
logic       uart_tx          ;//UART���ͣ�1bit
logic       uart_busy        ;//UART����æ�ź�

//����50MHzʱ�Ӽ���
bit sys_clk  ;
initial begin
  sys_clk = 0;
  forever
  #10 sys_clk = !sys_clk;
end

//������λ����
bit  sys_reset;
initial begin
  sys_reset = 1;
  #1000
  sys_reset = 0;
end

//���������
always @(posedge o_uart_clk)begin
  if(sys_reset)
    sim_count <= 0;
  else
    sim_count <= sim_count + 1'b1;
end

//�����û����ݼ���
always @(posedge o_uart_clk)begin
  if(sys_reset)begin
    i_send_data_en <= 'd0;
    i_send_data    <= 'd0;
  end
  else if(sim_count == 10)begin
    i_send_data_en <= 'd1;
    i_send_data    <= {$random}%100;//������������������
  end
  else begin
    i_send_data_en <= 'd0;
  end
end

//����uart_baud_rateģ��
uart_baud_rate uart_baud_rate(
  .sys_clk            (sys_clk           ),
  .sys_reset          (sys_reset         ),
  .i_uart_bps         ('d115200          ),//����������Ϊ115200
  .o_uart_clk         (o_uart_clk        ));

//����uart_sendģ��
uart_send uart_send(
  .sys_clk            (o_uart_clk       ),
  .sys_reset          (sys_reset        ),
  .i_send_data        (i_send_data      ),
  .i_send_data_en     (i_send_data_en   ),
  .uart_tx            (uart_tx          ),
  .uart_busy          (uart_busy        ));

//����uart_receiveģ��
uart_receive uart_receive(
  .sys_clk            (o_uart_clk       ),
  .sys_reset          (sys_reset        ),
  .uart_rx            (uart_tx          ),
  .o_receive_data     (o_receive_data   ),
  .o_receive_data_en  (o_receive_data_en));

endmodule
