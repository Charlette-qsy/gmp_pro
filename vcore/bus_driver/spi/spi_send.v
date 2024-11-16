//ʱ��߶�Ԥ����ָ��
`timescale 1ns / 1ps

//ģ������spi_send
module spi_send(
input       sys_clk          , //ϵͳʱ�ӣ�Ƶ��Ϊ50MHz
input       sys_reset        , //ϵͳ��λ���ߵ�ƽ��Ч
input[15:0] i_data           , //���Ͳ�������
input       i_data_en        , //���Ͳ�������ʹ��
output      spi_clk          , //SPI����ʱ�ӣ�50MHz
output      spi_csn          , //SPIƬѡ���͵�ƽ��Ч
output      spi_sdi          );//SPI��������

parameter    spi_idle       = 4'h1;//��״̬
parameter    spi_send_state = 4'h2;//��������״̬
parameter    spi_send_gap   = 4'h4;//���ͼ��״̬
parameter    spi_send_end   = 4'h8;//���ͽ���״̬

reg     [3:0] spi_cstate           ;//��ǰ״̬
reg     [3:0] spi_nstate           ;//��һ״̬
reg     [4:0] send_cnt             ;//��������״̬������
reg     [31:0]send_gap_cnt         ;//���ͼ��״̬������
reg     [15:0]data_reg1            ;//��������
reg           dac_clk_reg1         ;//SPIʱ��
reg           dac_csn_reg1         ;//SPIƬѡ
reg           dac_sdi_reg1         ;//SPI����

//��ǰ״̬��ת
always @(posedge sys_clk)begin
  if(sys_reset)
    spi_cstate <= spi_idle;
  else
    spi_cstate <= spi_nstate;
end

//��һ״̬��ת
always @(*) begin
  spi_nstate = spi_idle;//״̬����ʼ��
  case(spi_cstate)
    spi_idle:begin
      if(i_data_en == 1'b1)//�������ݿ�ʼ
        spi_nstate = spi_send_state;
      else
        spi_nstate = spi_idle; 
    end
    spi_send_state:begin
      if(send_cnt == 'd15)//�������ݽ���
        spi_nstate = spi_send_gap;
      else
        spi_nstate = spi_send_state;   
    end
    spi_send_gap:begin
      if(send_gap_cnt == 'd100)//�������ݷ��ͼ������
        spi_nstate = spi_send_end;
      else
        spi_nstate = spi_send_gap;
    end
    spi_send_end:begin
      spi_nstate = spi_idle;
    end
    default:begin
      spi_nstate = spi_idle;//��ֹ״̬���ܷ�
    end
  endcase
end

//��������״̬������������������״̬������������
always @(posedge sys_clk)begin
  if(sys_reset)
    send_cnt <= 'd0;
  else if(spi_cstate == spi_send_state)
    send_cnt <= send_cnt + 'd1;
  else
    send_cnt <= 'd0;
end

//���ͼ��״̬������������������״̬������������
always @(posedge sys_clk)begin
  if(sys_reset)
    send_gap_cnt <= 'd0;
  else if(spi_cstate == spi_send_gap)
    send_gap_cnt <= send_gap_cnt + 'd1;
  else
    send_gap_cnt <= 'd0;
end

//�Ĵ淢������
always @(posedge sys_clk)begin
  if(sys_reset)
    data_reg1 <= 'd0;
  else if(spi_cstate == spi_idle)begin
    data_reg1 <= i_data;
  end
end

//SPI����ʱ�����
always @( * )begin
  if(dac_csn_reg1)
  //ƬѡΪ�ߣ�SPI��ʱ�����
    dac_clk_reg1 = 1'b0;
  else
  //ƬѡΪ�ͣ�SPIʱ�����
    dac_clk_reg1 = ~sys_clk;
end

//SPIƬѡ�ź����
always @(posedge sys_clk)begin
  if(sys_reset)
    dac_csn_reg1 <= 'd1;
  else if(spi_cstate == spi_send_state)//��������ʱ������Ƭѡ
    dac_csn_reg1 <= 'd0;
  else
    dac_csn_reg1 <= 'd1;
end

//SPI�����������
always @(posedge sys_clk)begin
  if(sys_reset)
    dac_sdi_reg1 <= 'd0;
  //��������״̬���������ݣ��ȷ��������ݸ�λ���ٷ��������ݵ�λ
  else if(spi_cstate == spi_send_state)begin
    case(send_cnt)
      'd0 :dac_sdi_reg1 <= data_reg1[15];//MSB(15bit)
      'd1 :dac_sdi_reg1 <= data_reg1[14];//MSB(14bit)
      'd2 :dac_sdi_reg1 <= data_reg1[13];//MSB(13bit)
      'd3 :dac_sdi_reg1 <= data_reg1[12];//MSB(12bit)
      'd4 :dac_sdi_reg1 <= data_reg1[11];//MSB(11bit)
      'd5 :dac_sdi_reg1 <= data_reg1[10];//MSB(10bit)
      'd6 :dac_sdi_reg1 <= data_reg1[09];//MSB(09bit)
      'd7 :dac_sdi_reg1 <= data_reg1[08];//MSB(08bit)
      'd8 :dac_sdi_reg1 <= data_reg1[07];//MSB(07bit)
      'd9 :dac_sdi_reg1 <= data_reg1[06];//MSB(06bit)
      'd10:dac_sdi_reg1 <= data_reg1[05];//MSB(05bit)
      'd11:dac_sdi_reg1 <= data_reg1[04];//MSB(04bit)
      'd12:dac_sdi_reg1 <= data_reg1[03];//MSB(03bit)
      'd13:dac_sdi_reg1 <= data_reg1[02];//MSB(02bit)
      'd14:dac_sdi_reg1 <= data_reg1[01];//MSB(01bit)
      'd15:dac_sdi_reg1 <= data_reg1[00];//LSB(00bit)
      default:dac_sdi_reg1 <= 'd0;
    endcase
  end
  else dac_sdi_reg1 <= 'd0;
end

assign spi_clk = dac_clk_reg1;
assign spi_csn = dac_csn_reg1;
assign spi_sdi = dac_sdi_reg1;

endmodule
