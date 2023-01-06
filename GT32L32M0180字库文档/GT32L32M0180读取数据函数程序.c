/***************************************
ASCII ����
ASCIICode����ʾASCII �루8bits��
BaseAdd��˵�������ֿ���оƬ�е���ʼ��ַ��
r_dat_bat�� �Ƕ��������ݺ�����
DZ_Data���Ǳ�������ĵ������ݵ����顣
****************************************/
u8  ASCII_GetData(u8 ASCIICode,u32 BaseAdd)
{
	if((ASCIICode >= 0x20)&&(ASCIICode<=0x7e))
	{
	  switch(BaseAdd)
	  {
          case 0x100000: r_dat_bat((ASCIICode-0x20)*8+BaseAdd,8,DZ_Data); //5X7
                         break ;
          case 0x100300: r_dat_bat((ASCIICode-0x20)*8+BaseAdd,8,DZ_Data); //7X8
                         break ;
          case 0x100600: r_dat_bat((ASCIICode-0x20)*8+BaseAdd,8,DZ_Data); //7X8 Fat
                         break ;
          case 0x100900: r_dat_bat((ASCIICode-0x20)*12+BaseAdd,12,DZ_Data); //6X12
                         break ;
          case 0x100D80: r_dat_bat((ASCIICode-0x20)*16+BaseAdd,16,DZ_Data); //8X16
                         break ;
          case 0x101580: r_dat_bat((ASCIICode-0x20)*16+BaseAdd,16,DZ_Data); // 8X16 Fat
                         break ;
          case 0x101B80: r_dat_bat((ASCIICode-0x20)*48+BaseAdd,48,DZ_Data); //12X24
                         break ;
          case 0x102D80: r_dat_bat((ASCIICode-0x20)*64+BaseAdd,64,DZ_Data); //16X32
                         break ;
          case 0x104580: r_dat_bat((ASCIICode-0x20)*64+BaseAdd,64,DZ_Data); //16X32 Fat
                         break ;
          case 0x105D80: r_dat_bat((ASCIICode-0x20)*26+BaseAdd+2,24,DZ_Data); //12X12 A
                         break ;
          case 0x106740: r_dat_bat((ASCIICode-0x20)*34+BaseAdd+2,32,DZ_Data); //16X16 Arial
                         break ;
          case 0x107400: r_dat_bat((ASCIICode-0x20)*74+BaseAdd+2,72,DZ_Data); //24X24
                         break ;
          case 0x108FC0: r_dat_bat((ASCIICode-0x20)*130+BaseAdd+2,128,DZ_Data); //32X32
                         break ;
          case 0x10C080: r_dat_bat((ASCIICode-0x20)*26+BaseAdd+2,24,DZ_Data); //12X12 T
                         break ;
          case 0x10CA50: r_dat_bat((ASCIICode-0x20)*34+BaseAdd+2,32,DZ_Data); //16X16 T
                         break ;
          case 0x10D740: r_dat_bat((ASCIICode-0x20)*74+BaseAdd+2,72,DZ_Data); //24X24 T
                         break ;
          case 0x10F340: r_dat_bat((ASCIICode-0x20)*130+BaseAdd+2,128,DZ_Data); //32X32 T
                         break ;
          default:       break ;
	  }
	 return 1;
	}
    else  return 0;
}

/*****************************************************************************
�������ַ����ַ�
˵����																					  --------------------
�˲�������Ϊ0 1 2 3 4 5 6 7 8 9 , . �� $ ��
Squence����ʾ �ַ�˳�򣬴�0��ʼ������
BaseAdd��˵�������ֿ���оƬ�е���ʼ��ַ��
Address����Ӧ�ַ�������оƬ�е��ֽڵ�ַ��
******************************************************************************/
u8  Dig_Ch_GetData(u8 Sequence,u32 BaseAdd)
{
	  switch(BaseAdd)
	  {
          case 0x112400: r_dat_bat(Sequence * 56+ BaseAdd,56,DZ_Data); //14X28
                         break ;
          case 0x112748: r_dat_bat(Sequence * 120+ BaseAdd,120,DZ_Data); //20X40
                         break ;
          case 0x112CE8: r_dat_bat(Sequence * 114+ BaseAdd+2,112,DZ_Data); //28X28
                         break ;
          case 0x113396: r_dat_bat(Sequence * 202+ BaseAdd+2,200,DZ_Data); //40X40
                         break ;
          default:       break ;
	  }
	 return 1;
}

/***************************************************************************************************
12x12����GB18030����&�ַ�
������u32 GB18030_12_GetData(u8 c1, u8 c2, u8 c3, u8 c4)
���ܣ����㺺�ֵ�����оƬ�еĵ�ַ����ȡ�������ݵ�ָ�����顣
��������������ͨ������c1,c2���룬c3=0;c4=0.
ע��12x12ΪGBK�ַ����������ֽ�����
���أ����ֵ�����ֽڵ�ַ(byte address)��
����û��ǰ� word mode ��ȡ�������ݣ������ ַ(word address)Ϊ�ֽڵ�ַ����2��
����word address = byte address / 2 . ���磺
BaseAdd: ˵�����ֵ����������ֿ�оƬ�е���ʼ��ַ����BaseAdd��0x093D0E��
�������ֵ�����Ϊ0xb0a1,��byte address = GB18030_12_GetData(0xb0,0xa1,0x00,0x00) *24+BaseAdd ,
word address = byte address / 2	.
****************************************************************************************************/
u32 GB18030_12_GetData(u8 c1, u8 c2, u8 c3, u8 c4)
{
    u32 h=0;
    u32 BaseAdd=0x113D0E;
    if(c2==0x7f)
    {
        r_dat_bat(BaseAdd,24,DZ_Data);
        return (BaseAdd);
    }
    if(c1>=0xA1 && c1 <= 0xa9 && c2>=0xa1) //Section 1
        h= (c1 - 0xA1) * 94 + (c2 - 0xA1);
    else if(c1>=0xa8 && c1 <= 0xa9 && c2<0xa1) //Section 5
    {
        if(c2>0x7f)
            c2--;
        h=(c1-0xa8)*96 + (c2-0x40)+846;
    }
    if(c1>=0xb0 && c1 <= 0xf7 && c2>=0xa1) //Section 2
        h= (c1 - 0xB0) * 94 + (c2 - 0xA1)+1038;
    else if(c1<0xa1 && c1>=0x81 && c2>=0x40 ) //Section 3
    {
        if(c2>0x7f)
           c2--;
        h=(c1-0x81)*190 + (c2-0x40) + 1038 +6768;
    }
    else if(c1>=0xaa && c2<0xa1) //Section 4
    {
        if(c2>0x7f)
           c2--;
        h=(c1-0xaa)*96 + (c2-0x40) + 1038 +12848;
    }
    r_dat_bat(h*24+BaseAdd,24,DZ_Data);
    return(h*24+BaseAdd);
}

/***************************************************************************************************
16x16����GB18030����&�ַ�
������u8 GB18030_16_GetData(u8 c1, u8 c2, u8 c3, u8 c4)
���ܣ����㺺�ֵ�����оƬ�еĵ�ַ,��ȡ�������ݵ�ָ�����顣
������c1,c2,c3,c4��
4�ֽں�������ͨ������c1,c2,c3,c4���룬˫�ֽ�����ͨ������c1,c2 ���룬c3=0,c4=0
���أ����ֵ�����ֽڵ�ַ(byte address)��
����û��ǰ� word mode ��ȡ�������ݣ������ַ(word address)Ϊ�ֽڵ�ַ����2��
����word address = byte address / 2 . ���磺
BaseAdd: ˵�����ֵ����������ֿ�оƬ�е���ʼ��ַ����BaseAdd��0x114FDE;
 �������ֵ�����Ϊ0xb0a1,��byte address = GB18030_16_GetData(0xb0,0xa1,0x00,0x00) *32+BaseAdd;
word address = byte address / 2
��.���ֵ�����Ϊ0x8139ee39,��byte address = GB18030_16_GetData(0x81,0x39,0xee,0x39) *32+ BaseAdd
word address = byte address / 2
****************************************************************************************************/
u32 GB18030_16_GetData(u8 c1, u8 c2, u8 c3, u8 c4)
{
    u32 h=0;
    u32 BaseAdd=0x194FDE;
    if(c2==0x7f)
    {
        r_dat_bat(BaseAdd,32,DZ_Data);
        return (BaseAdd);
    }
    if(c1>=0xA1 && c1 <= 0xa9 && c2>=0xa1) //Section 1
        h= (c1 - 0xA1) * 94 + (c2 - 0xA1);
    else if(c1>=0xa8 && c1 <= 0xa9 && c2<0xa1) //Section 5
    {
        if(c2>0x7f) c2--;
        h=(c1-0xa8)*96 + (c2-0x40)+846;
    }
    if(c1>=0xb0 && c1 <= 0xf7 && c2>=0xa1) //Section 2
        h= (c1 - 0xB0) * 94 + (c2 - 0xA1)+1038;
    else if(c1<0xa1 && c1>=0x81 && c2>=0x40 ) //Section 3
    {
        if(c2>0x7f) c2--;
        h=(c1-0x81)*190 + (c2-0x40) + 1038 +6768;
    }
    else if(c1>=0xaa && c2<0xa1) //Section 4
    {
        if(c2>0x7f) c2--;
        h=(c1-0xaa)*96 + (c2-0x40) + 1038 +12848;
    }
    else if(c1==0x81 && c2>=0x39) //���ֽ���1
    {
        h =1038 + 21008+(c3-0xEE)*10+c4-0x39;
    }
    else if(c1==0x82)//���ֽ���2
    {
        h =1038 + 21008+161+(c2-0x30)*1260+(c3-0x81)*10+c4-0x30;
    }
    r_dat_bat(h*32+BaseAdd,32,DZ_Data);
    return(h*32+BaseAdd);
}

/***************************************************************************************************
24x24����GB18030����&�ַ�
������u8 GB18030_24_GetData(u8 c1, u8 c2, u8 c3, u8 c4)
���ܣ����㺺�ֵ�����оƬ�еĵ�ַ,��ȡ�������ݵ�ָ�����顣
������c1,c2,c3,c4��
4�ֽں�������ͨ������c1,c2,c3,c4���룬˫�ֽ�����ͨ������c1,c2 ���룬c3=0,c4=0
���أ����ֵ�����ֽڵ�ַ(byte address)��
����û��ǰ� word mode ��ȡ�������ݣ������ַ(word address)Ϊ�ֽڵ�ַ����2��
����word address = byte address / 2 . ���磺
BaseAdd: ˵�����ֵ����������ֿ�оƬ�е���ʼ��ַ����BaseAdd��0x1F43DE;
 �������ֵ�����Ϊ0xb0a1,��byte address = GB18030_24_GetData(0xb0,0xa1,0x00,0x00) *72+BaseAdd;
word address = byte address / 2
��.���ֵ�����Ϊ0x8139ee39,��byte address = GB18030_24_GetData(0x81,0x39,0xee,0x39) *72+ BaseAdd
word address = byte address / 2
****************************************************************************************************/
u32 GB18030_24_GetData(u8 c1, u8 c2, u8 c3, u8 c4)
{
    u32 h=0;
    u32 BaseAdd=0x2743DE;
    if(c2==0x7f)
    {
        r_dat_bat(BaseAdd,72,DZ_Data);
        return (BaseAdd);
    }
    if(c1>=0xA1 && c1 <= 0xa9 && c2>=0xa1) //Section 1
        h= (c1 - 0xA1) * 94 + (c2 - 0xA1);
    else if(c1>=0xa8 && c1 <= 0xa9 && c2<0xa1) //Section 5
    {
        if(c2>0x7f) c2--;
        h=(c1-0xa8)*96 + (c2-0x40)+846;
    }
    if(c1>=0xb0 && c1 <= 0xf7 && c2>=0xa1) //Section 2
        h= (c1 - 0xB0) * 94 + (c2 - 0xA1)+1038;
    else if(c1<0xa1 && c1>=0x81 && c2>=0x40 ) //Section 3
    {
        if(c2>0x7f) c2--;
        h=(c1-0x81)*190 + (c2-0x40) + 1038 +6768;
    }
    else if(c1>=0xaa && c2<0xa1) //Section 4
    {
        if(c2>0x7f) c2--;
        h=(c1-0xaa)*96 + (c2-0x40) + 1038 +12848;
    }
    else if(c1==0x81 && c2>=0x39) //���ֽ���1
    {
        h =1038 + 21008+(c3-0xEE)*10+c4-0x39;
    }
    else if(c1==0x82)//���ֽ���2
    {
        h =1038 + 21008+161+(c2-0x30)*1260+(c3-0x81)*10+c4-0x30;
    }
    r_dat_bat(h*72+BaseAdd,72,DZ_Data);
    return(h*72+BaseAdd);
}

/***************************************************************************************************
32x32����GB18030����&�ַ�
������u32 GB18030_32_GetData (u8 c1, u8 c2, u8 c3, u8 c4)
���ܣ����㺺�ֵ�����оƬ�еĵ�ַ
������c1,c2,c3,c4��4�ֽں�������ͨ������c1,c2,c3,c4���룬˫�ֽ�����ͨ������c1,c2�� �룬c3=0,c4=0
���أ����ֵ�����ֽڵ�ַ(byte address)������û��ǰ� word mode ��ȡ�������ݣ�
����� ַ(word address)Ϊ�ֽڵ�ַ����2������word address = byte address / 2 .
���磺BaseAdd: ˵�����ֵ����������ֿ�оƬ�е���ʼ��ַ����BaseAdd��0x47AE10; �������ֵ�����Ϊ0xb0a1,
��byte address = gt(0xb0,0xa1,0x00,0x00) *128+BaseAdd word address = byte address / 2
��.���ֵ�����Ϊ0x8139ee39,��byte address = gt(0x81, 0x39,0xee,0x39) *128+ BaseAdd word address = byte address / 2
****************************************************************************************************/
u32 GB18030_32_GetData (u8 c1, u8 c2, u8 c3, u8 c4)
{
    u32 h=0;
    u32  BaseAdd=0x47AE10;
    if(c2==0x7f)
    {
        r_dat_bat(BaseAdd,128,DZ_Data);
        return (BaseAdd);
    }
    if(c1>=0xA1 && c1 <= 0xAB && c2>=0xa1) //Section 1
        h= (c1 - 0xA1) * 94 + (c2 - 0xA1);
    else if(c1>=0xa8 && c1 <= 0xa9 && c2<0xa1) //Section 5
    {
        if(c2>0x7f) c2--;
        h=(c1-0xa8)*96 + (c2-0x40)+846;
    }
    if(c1>=0xb0 && c1 <= 0xf7 && c2>=0xa1) //Section 2
        h= (c1 - 0xB0) * 94 + (c2 - 0xA1)+1038-192;
    else if(c1<0xa1 && c1>=0x81 && c2>=0x40) //Section 3
    {
        if(c2>0x7f) c2--;
        h=(c1-0x81)*190 + (c2-0x40) + 1038 +6768-192;
    }
    else if(c1>=0xaa && c2<0xa1) //Section 4
    {
        if(c2>0x7f) c2--; h=(c1-0xaa)*96 + (c2-0x40) + 1038 +12848-192;
    }
    else if(c1==0x81 && c2>=0x39) //���ֽ���1
    {
        h =1038 + 21008+(c3-0xEE)*10+c4-0x39-192;
    }
    else if(c1==0x82)//���ֽ���2
    {
        h =1038 + 21008+161+(c2-0x30)*1260+(c3-0x81)*10+c4-0x30-192;
    }
    r_dat_bat(h*128+BaseAdd,128,DZ_Data);
    return(h*128+BaseAdd);
}

/**********************************************************************
EAN13��������ó���
������DWORD* BAR_CODE(int* BAR_NUM)
���ܣ�������������תΪ��Ӧ������ͼ�ε�ַ��
������int* BAR_NUM ��������������ָ�룬BAR_NUM[13]�������13�����֡�
���أ�����DWORD BAR_PIC_ADDR[13];���ڴ�Ŷ�Ӧ��ַ�����ش�����ָ�롣
***********************************************************************/

u32 BAR_CODE13(u8 * BAR_NUM)
{
    u32 i,BaseAddr=0x478FD2;
    BAR_PIC_ADDR[0]=BAR_NUM[0]*54+540*0+ BaseAddr;
    BAR_PIC_ADDR[1]=BAR_NUM[1]*54+540*1+ BaseAddr;
    switch(BAR_NUM[0])
    {
        case 0:
            for(i=2;i<=6;i++)
            {
            BAR_PIC_ADDR[i]=BAR_NUM[i]*54+540*1+ BaseAddr;
            }
        break;
        case 1:
            BAR_PIC_ADDR[2]=BAR_NUM[2]*54+540*1+ BaseAddr;
            BAR_PIC_ADDR[3]=BAR_NUM[3]*54+540*2+ BaseAddr;
            BAR_PIC_ADDR[4]=BAR_NUM[4]*54+540*1+ BaseAddr;
            BAR_PIC_ADDR[5]=BAR_NUM[5]*54+540*2+ BaseAddr;
            BAR_PIC_ADDR[6]=BAR_NUM[6]*54+540*2+ BaseAddr;
        break;
        case 2:
            BAR_PIC_ADDR[2]=BAR_NUM[2]*54+540*1+ BaseAddr;
            BAR_PIC_ADDR[3]=BAR_NUM[3]*54+540*2+ BaseAddr;
            BAR_PIC_ADDR[4]=BAR_NUM[4]*54+540*2+ BaseAddr;
            BAR_PIC_ADDR[5]=BAR_NUM[5]*54+540*1+ BaseAddr;
            BAR_PIC_ADDR[6]=BAR_NUM[6]*54+540*2+ BaseAddr;
        break;
        case 3:
            BAR_PIC_ADDR[2]=BAR_NUM[2]*54+540*1+ BaseAddr;
            BAR_PIC_ADDR[3]=BAR_NUM[3]*54+540*2+ BaseAddr;
            BAR_PIC_ADDR[4]=BAR_NUM[4]*54+540*2+ BaseAddr;
            BAR_PIC_ADDR[5]=BAR_NUM[5]*54+540*2+ BaseAddr;
            BAR_PIC_ADDR[6]=BAR_NUM[6]*54+540*1+ BaseAddr;
        break;
        case 4:
            BAR_PIC_ADDR[2]=BAR_NUM[2]*54+540*2+ BaseAddr;
            BAR_PIC_ADDR[3]=BAR_NUM[3]*54+540*1+ BaseAddr;
            BAR_PIC_ADDR[4]=BAR_NUM[4]*54+540*1+ BaseAddr;
            BAR_PIC_ADDR[5]=BAR_NUM[5]*54+540*2+ BaseAddr;
            BAR_PIC_ADDR[6]=BAR_NUM[6]*54+540*2+ BaseAddr;
        break;
        case 5:
            BAR_PIC_ADDR[2]=BAR_NUM[2]*54+540*2+ BaseAddr;
            BAR_PIC_ADDR[3]=BAR_NUM[3]*54+540*2+ BaseAddr;
            BAR_PIC_ADDR[4]=BAR_NUM[4]*54+540*1+ BaseAddr;
            BAR_PIC_ADDR[5]=BAR_NUM[5]*54+540*1+ BaseAddr;
            BAR_PIC_ADDR[6]=BAR_NUM[6]*54+540*2+ BaseAddr;
        break;
        case 6:
            BAR_PIC_ADDR[2]=BAR_NUM[2]*54+540*2+ BaseAddr;
            BAR_PIC_ADDR[3]=BAR_NUM[3]*54+540*2+ BaseAddr;
            BAR_PIC_ADDR[4]=BAR_NUM[4]*54+540*2+ BaseAddr;
            BAR_PIC_ADDR[5]=BAR_NUM[5]*54+540*1+ BaseAddr;
            BAR_PIC_ADDR[6]=BAR_NUM[6]*54+540*1+ BaseAddr;
        break;
        case 7:
            BAR_PIC_ADDR[2]=BAR_NUM[2]*54+540*2+ BaseAddr;
            BAR_PIC_ADDR[3]=BAR_NUM[3]*54+540*1+ BaseAddr;
            BAR_PIC_ADDR[4]=BAR_NUM[4]*54+540*2+ BaseAddr;
            BAR_PIC_ADDR[5]=BAR_NUM[5]*54+540*1+ BaseAddr;
            BAR_PIC_ADDR[6]=BAR_NUM[6]*54+540*2+ BaseAddr;
        break;
        case 8:
            BAR_PIC_ADDR[2]=BAR_NUM[2]*54+540*2+ BaseAddr;
            BAR_PIC_ADDR[3]=BAR_NUM[3]*54+540*1+ BaseAddr;
            BAR_PIC_ADDR[4]=BAR_NUM[4]*54+540*2+ BaseAddr;
            BAR_PIC_ADDR[5]=BAR_NUM[5]*54+540*2+ BaseAddr;
            BAR_PIC_ADDR[6]=BAR_NUM[6]*54+540*1+ BaseAddr;
        break;
        case 9:
            BAR_PIC_ADDR[2]=BAR_NUM[2]*54+540*2+ BaseAddr;
            BAR_PIC_ADDR[3]=BAR_NUM[3]*54+540*2+ BaseAddr;
            BAR_PIC_ADDR[4]=BAR_NUM[4]*54+540*1+ BaseAddr;
            BAR_PIC_ADDR[5]=BAR_NUM[5]*54+540*2+ BaseAddr;
            BAR_PIC_ADDR[6]=BAR_NUM[6]*54+540*1+ BaseAddr;
        break;
    }
    BAR_PIC_ADDR[7]=BAR_NUM[7]*54+540*3+ BaseAddr;
    for(i=8;i<=11;i++)
    {
        BAR_PIC_ADDR[i]=BAR_NUM[i]*54+540*4+ BaseAddr;
    }
    BAR_PIC_ADDR[12]=BAR_NUM[12]*54+540*5+ BaseAddr;
    return BAR_PIC_ADDR[0];
}

/***********************************************************************************************
GB/T 18347-2001(CODE128)��������ó���
������u32 BAR_CODE128(u8 *BAR_NUM)
���ܣ�������������תΪ��Ӧ������ͼ�ε�ַ
������u8 *BAR_NUM ��������������ָ��,BAR_NUM[4]�������4��������ASCII��(����ȡֵΪ0~94)��
���أ�����u32 BAR_PIC_ADDR[7] �����ڴ�Ŷ�Ӧ��ַ����������ָ�롣
�����ַ��BaseAddr=0x3F2ED3;
��ʼ����3��ģʽ
��flag=1ʱΪCode-128-A;
��flag=2ʱΪCode-128-B;
��flag=3ʱΪCode-128-C;
***********************************************************************************************/
u32 BAR_CODE128(u8 *BAR_NUM,u8 flag)
{
    u32 BaseAddr=0x479C7A;
    u8 i;
    for(i=0;i<7;i++)
    {
        switch(flag)
        {
            case 1 :
                if(i==0)
                {
                    BAR_PIC_ADDR[i]=103*40+BaseAddr;
                }
                else if(i==1||i==2||i==3||i==4)
                {
                    BAR_PIC_ADDR[i]=BAR_NUM[i-1]*40+BaseAddr;
                }
                else if(i==5)
                {
                    BAR_PIC_ADDR[i]=95*40+BaseAddr;
                }
                else if(i==6)
                {
                    BAR_PIC_ADDR[i]=106*40+BaseAddr;
                }
            break;

            case 2 :
                if(i==0)
                {
                    BAR_PIC_ADDR[i]=104*40+BaseAddr;
                }
                else if(i==1||i==2||i==3||i==4)
                {
                    BAR_PIC_ADDR[i]=BAR_NUM[i-1]*40+BaseAddr;
                }
                else if(i==5)
                {
                    BAR_PIC_ADDR[i]=95*40+BaseAddr;
                }
                else if(i==6)
                {
                    BAR_PIC_ADDR[i]=106*40+BaseAddr;
                }
            break;

            case 3 :
                if(i==0)
                {
                    BAR_PIC_ADDR[i]=105*40+BaseAddr;
                }
                else if(i==1||i==2||i==3||i==4)
                {
                    BAR_PIC_ADDR[i]=BAR_NUM[i-1]*40+BaseAddr;
                }
                else if(i==5)
                {
                    BAR_PIC_ADDR[i]=95*40+BaseAddr;
                }
                else if(i==6)
                {
                    BAR_PIC_ADDR[i]=106*40+BaseAddr;
                }
            break;

            default:
            break;
        }
    }
    return BAR_PIC_ADDR[0];
}

/***********************************
���ߵ��ó���
������u32 Antenna_CODE_12X12_GetData(u8 NUM)
���ܣ���ȡ12X12���ߵ��õ�ַ,ȡ���������ݡ�
������NUM 0123���������ź�ǿ�ȡ�
���أ����ݵ�ַ
***********************************/
u32 Antenna_CODE_12X12_GetData(u8 NUM)
{
    u32 Address,BaseAdd=0x47AD32;
    Address=NUM*24+BaseAdd;
    r_dat_bat(Address,24,DZ_Data);
    return Address;
}

/**********************************
��ص��ó���
������u32 Battery_CODE_12X12_GetData(u8 NUM)
���ܣ���ȡ12X12��ص��õ�ַ,ȡ���������ݡ�
������NUM 0123�����ص�����
���أ����ݵ�ַ
**********************************/
u32 Battery_CODE_12X12_GetData(u8  NUM)
{
    u32 Address, BaseAdd=0x47ADAA;
    Address=BaseAdd+NUM*24;
    r_dat_bat(Address,24,DZ_Data);
    return Address;
}
/***************************************************************************
UNICODEתGBK���ӳ���㷨������������,ת��ȫ��˫�ֽ�����
GB_Addressת��֮���GB��Ĵ�ŵ�ַ��
������u32 U2G(u16 Unicode)
���ܣ���UNICODE��ת��ΪGB��,
������u16 Unicode,��ʾ�����UNICODE�롣
���أ���Ӧ��GB�����ֿ��д�ŵĵ�ַ��
��ע:��ȡ��Ӧ��ַ2�ֽ����ݼ�Ϊunicode��Ӧ��GB�룩��
ת�����ʼ��ַ�� BaseAdd��0x3EA90E;
***************************************************************************/
u32 U2G(u16 unicode)
{
    u32 BaseAdd=0x46A90E;
    u32 Address,U_Start_Addr;
    if(unicode<=0x0451&&unicode>=0x00a0)
    {
        U_Start_Addr=0;
        Address= U_Start_Addr +(unicode-0x00a0)*2;
    }
    else if(unicode<=0x2642&&unicode>=0x2010)
    {
        U_Start_Addr =1892;
        Address= U_Start_Addr +(unicode-0x2010)*2;
    }
    else if(unicode<=0x33d5&&unicode>=0x3000)
    {
        U_Start_Addr =5066;
        Address= U_Start_Addr +(unicode-0x3000)*2;
    }
    else if(unicode<=0x9fa5&&unicode>=0x4e00)
    {
        U_Start_Addr =7030;
        Address= U_Start_Addr +(unicode-0x4e00)*2;
    }
    else if(unicode<=0xfe6b&&unicode>=0xfe30)
    {
        U_Start_Addr =48834;
        Address= U_Start_Addr +(unicode-0xfe30)*2;
    }
    else if(unicode<=0xff5e&&unicode>=0xff01)
    {
        U_Start_Addr =48954;
        Address= U_Start_Addr +(unicode-0xff01)*2;
    }
    else if(unicode<=0xffe5&&unicode>=0xffe0)
    {
        U_Start_Addr =49142;
        Address= U_Start_Addr +(unicode-0xffe0)*2;
    }
    else if (unicode<=0xFA29&&unicode>=0xF92C)
    {
        U_Start_Addr =49312;
        Address= U_Start_Addr +(unicode-0xF92C)*2;
    }
    else if(unicode<=0xE864&&unicode>=0xE816)
    {
        U_Start_Addr =49820;
        Address= U_Start_Addr +(unicode-0xE816)*2;
    }
    else if(unicode<=0x2ECA&&unicode>=0x2E81)
    {
        U_Start_Addr =49978;
        Address= U_Start_Addr +(unicode-0x2E81)*2;
    }
    else if(unicode<=0x49B7&&unicode>=0x4947)
    {
        U_Start_Addr =50126;
        Address= U_Start_Addr +(unicode-0x4947)*2;
    }
    else if(unicode<=0x4DAE&&unicode>=0x4C77)
    {
        U_Start_Addr =50352;
        Address= U_Start_Addr +(unicode-0x4C77)*2;
    }
    else if(unicode<=0x3CE0&&unicode>=0x3447)
    {
        U_Start_Addr =50976;
        Address= U_Start_Addr +(unicode-0x3447)*2;
    }
    else if(unicode<=0x478D&&unicode>=0x4056)
    {
        U_Start_Addr =55380;
        Address= U_Start_Addr +(unicode-0x4056)*2;
    }
    Address+=BaseAdd;
    r_dat_bat(Address,2,GBCode);
    return Address;
}
/**********************************************************
UNICODEתGBK���ӳ���㷨,��1&3�ַ���
������WORD U2G(WORD Unicode)
���ܣ���UNICODE��ת��ΪGB��,
ע����Ӧ����1��&3����
������WORD Unicode,��ʾ�����UNICODE�롣
���أ���Ӧ��GB�����ֿ��д�ŵĵ�ַ��
��ע:��ȡ��Ӧ��ַ2�ֽ����ݼ�Ϊunicode��Ӧ��GB�룩��
***********************************************************/

u16 U2G_13(u16 Unicode)
{
    u16 GB_Code;
    u16 UG[]={
    0x3000,0x3001,0x3002,0x00b7,0x02c9,0x02c7,0x00a8,
    0x3003,0x3005,0x2014, 0xff5e,0x2016,0x2026,0x2018,0x2019,0x201c,
    0x201d,0x3014,0x3015,0x3008, 0x3009,0x300a,0x300b,0x300c,0x300d,
    0x300e,0x300f,0x3016,0x3017,0x3010, 0x3011,0x00b1,0x00d7,0x00f7,
    0x2236,0x2227,0x2228,0x2211,0x220f,0x222a, 0x2229,0x2208,0x2237,
    0x221a,0x22a5,0x2225,0x2220,0x2312,0x2299,0x222b, 0x222e,0x2261,
    0x224c,0x2248,0x223d,0x221d,0x2260,0x226e,0x226f,0x2264, 0x2265,
    0x221e,0x2235,0x2234,0x2642,0x2640,0x00b0,0x2032,0x2033,0x2103,
    0xff04,0x00a4,0xffe0,0xffe1,0x2030,0x00a7,0x2116,0x2606,0x2605,
    0x25cb, 0x25cf,0x25ce,0x25c7,0x25c6,0x25a1,0x25a0,0x25b3,0x25b2,
    0x203b,0x2192, 0x2190,0x2191,0x2193,0x3013 };
    u32 i;
    if(Unicode>=0xff01&&Unicode<=0xffe5)//section 3
    {
        if(Unicode==0xff04)
            GB_Code=0xa1e7;
        if(Unicode==0xff5e)
            GB_Code=0xa1ab;
        if(Unicode==0xffe0)
            GB_Code=0xa1e9;
        if(Unicode==0xffe1)
            GB_Code=0xa1ea;
        if(Unicode==0xffe3)
            GB_Code=0xa3fe;
        if(Unicode==0xffe5)
            GB_Code=0xa3a4;
        else
            GB_Code=Unicode-0xff01+0xa3a1;
    }
    if(Unicode<=0x3013)
    {
        for(i=0;i<94;i++)
        {
            if(Unicode==UG[i])
                GB_Code=0xa1a1+i;
        }
    }
    GBCode[0]=GB_Code>>8;
    GBCode[1]=GB_Code&0xff;
    return GB_Code;
}
/***********************************************************
BIG5תGBKת���㷨
������u32 BIG5_G(u16 GBcode)
���ܣ�����BIG5���ӦGB���ŵ���ʼ��ַ
������B5code ����BIG5����˫�ֽ�
���أ���ӦGB���ŵ�ַ����ӦGB���λ��ǰ����λ�ں�
************************************************************/
u32 BIG5_G(u16 B5code)
{
    u32 Address,part_addr,BaseAddr=0x7F1E10;//ת������ַ;
    u8 TMP,B5_MSB,B5_LSB;
    B5_MSB= B5code >>8;
    B5_LSB= B5code &0x00ff;

    if(B5_MSB>=0xa1&&B5_MSB<=0xa3)
    {
        part_addr=0;
        TMP=0xa1;
    }
    else if(B5_MSB>=0xa4&&B5_MSB<=0xc6)
    {
        part_addr=816;
        TMP=0xa4;
    }
    else if(B5_MSB>=0xc9&&B5_MSB<=0xf9)
    {
        part_addr=11618; TMP=0xc9;
    }
    if(B5_LSB<=0x7e&&B5_LSB>=0x40)
    {
        Address=part_addr+((B5_MSB-TMP)*157+B5_LSB-0x40)*2+BaseAddr;
    }
    else if(B5_LSB<=0xfe&&B5_LSB>=0xa1)
    {
        Address=part_addr+((B5_MSB-TMP)*157+B5_LSB-0xa1+63)*2+BaseAddr;
    }
    r_dat_bat(Address,2,GBCode);
    return Address;
}


//���� ���ֿ��ж����ݺ���
/****************************************************
u8 r_dat_bat(u32 address,u8 byte_long,u8 *p_arr)��
˵����
Address  �� ��ʾ�ַ�������оƬ�е��ֽڵ�ַ��
byte_long�� �Ƕ����������ֽ�����
*p_arr   �� �Ǳ�������ĵ������ݵ����顣
*****************************************************/
u8 r_dat_bat(u32 address,u8 byte_long,u8 *p_arr)
{
    unsigned int j=0;
    CS_L;
    SendByte(address);//����03ָ��͵�ַ��
    for(j=0;j<byte_long;j++)
    {
        p_arr[j]=ReadByte();// ���ֿ�����������ݵ������С�
    }
    CS_H;
    return p_arr[0];
}

void SendByte(u32 cmd)
{
	u8 i;
	cmd=cmd|0x03000000;//0x03ָ����+��ַ��
	for(i=0;i<32;i++)
	{
		CLK_L;
		if(cmd&0x80000000)
			SI_H;
		else
			SI_L;
		CLK_H;
		cmd=cmd<<1;
	}
}

u8 ReadByte(void)
{
	u8 i;
	u8 dat=0;
	CLK_H;
	for(i=0;i<8;i++)
	{
		CLK_L;
		dat=dat<<1;
		if(SO)
			dat=dat|0x01;
		else
			dat&=0xfe;
		CLK_H	;
	}
	return dat;
}
