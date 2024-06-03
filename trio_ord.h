/************************************************************************************
	����

	�� �ڷ�� 2013�� 10�� 15�� ���� �ڷ��̸� ���� ����� ���ɼ��� �ֽ��ϴ�.
	�ڷ� ������ ���� ���� ��� ����ü�� ������� �ʾҴ��� Ȯ���Ͻñ� �ٶ��ϴ�.

	�ֽ� �ڷ�� ���������� ���� �ȳ��Ǹ� �ڵ� �ȳ�(OpenAPI Login��)�� �ϰ� ������ 
	�Խø� �� Ȯ���Ͻñ� �ٶ��ϴ�.

************************************************************************************/

////////////////////////////////////////
//	�ֽ� ELW
////////////////////////////////////////

typedef struct tagc8101InBlock    //�⺻�Է�
{
	char pswd_noz8                        [ 44];	char _pswd_noz8;                          //��й�ȣ             
	char issue_codez6                     [  6];	char _issue_codez6;                       //�����ȣ             
	char order_qtyz12                     [ 12];	char _order_qtyz12;                       //�ֹ�����             
	char order_unit_pricez10              [ 10];	char _order_unit_pricez10;                //�ֹ��ܰ�             
	char trade_typez2                     [  2];	char _trade_typez2;                       //�Ÿ�����             
	char shsll_pos_flagz1                 [  1];	char _shsll_pos_flagz1;                   //���ŵ����ɿ���       
	char trad_pswd_no_1z8                 [ 44];	char _trad_pswd_no_1z8;                   //�ŷ���й�ȣ1        
	char trad_pswd_no_2z8                 [ 44];	char _trad_pswd_no_2z8;                   //�ŷ���й�ȣ2        
} Tc8101InBlock;

typedef struct tagc8101OutBlock    //ȭ�����
{
	char order_noz10                      [ 10];	char _order_noz10;                        //�ֹ���ȣ             
	char order_qtyz12                     [ 12];	char _order_qtyz12;                       //�ֹ�����             
	char order_unit_pricez10              [ 10];	char _order_unit_pricez10;                //�ֹ��ܰ�             
} Tc8101OutBlock;

typedef struct tagc8101
{
	Tc8101InBlock                     c8101inblock                          ;  //�⺻�Է� 
	Tc8101OutBlock                    c8101outblock                         ;  //ȭ����� 
} Tc8101;

typedef struct tagc8102InBlock    //�⺻�Է�
{
	char pswd_noz8                        [ 44];	char _pswd_noz8;                          //��й�ȣ             
	char issue_codez6                     [  6];	char _issue_codez6;                       //�����ȣ             
	char order_qtyz12                     [ 12];	char _order_qtyz12;                       //�ֹ�����             
	char order_unit_pricez10              [ 10];	char _order_unit_pricez10;                //�ֹ��ܰ�             
	char trade_typez2                     [  2];	char _trade_typez2;                       //�Ÿ�����             
	char trad_pswd_no_1z8                 [ 44];	char _trad_pswd_no_1z8;                   //�ŷ���й�ȣ1        
	char trad_pswd_no_2z8                 [ 44];	char _trad_pswd_no_2z8;                   //�ŷ���й�ȣ2        
} Tc8102InBlock;

typedef struct tagc8102OutBlock    //ȭ�����
{
	char order_noz10                      [ 10];	char _order_noz10;                        //�ֹ���ȣ             
	char order_qtyz12                     [ 12];	char _order_qtyz12;                       //�ֹ�����             
	char order_unit_pricez10              [ 10];	char _order_unit_pricez10;                //�ֹ��ܰ�             
} Tc8102OutBlock;

typedef struct tagc8102
{
	Tc8102InBlock                     c8102inblock                          ;  //�⺻�Է� 
	Tc8102OutBlock                    c8102outblock                         ;  //ȭ����� 
} Tc8102;

typedef struct tagc8103InBlock    //�⺻�Է�
{
	char pswd_noz8                        [ 44];	char _pswd_noz8;                          //��й�ȣ             
	char issue_codez6                     [  6];	char _issue_codez6;                       //�����ȣ             
	char crctn_qtyz12                     [ 12];	char _crctn_qtyz12;                       //��������             
	char crctn_pricez10                   [ 10];	char _crctn_pricez10;                     //�����ܰ�             
	char orgnl_order_noz10                [ 10];	char _orgnl_order_noz10;                  //���ֹ���ȣ           
	char all_part_typez1                  [  1];	char _all_part_typez1;                    //��������             
	char trad_pswd_no_1z8                 [ 44];	char _trad_pswd_no_1z8;                   //�ŷ����1            
	char trad_pswd_no_2z8                 [ 44];	char _trad_pswd_no_2z8;                   //�ŷ����2            
} Tc8103InBlock;

typedef struct tagc8103OutBlock    //ȭ�����
{
	char orgnl_order_noz10                [ 10];	char _orgnl_order_noz10;                  //���ֹ���ȣ           
	char order_noz10                      [ 10];	char _order_noz10;                        //�ֹ���ȣ             
	char mom_order_noz10                  [ 10];	char _mom_order_noz10;                    //���ֹ���ȣ           
	char issue_codez6                     [  6];	char _issue_codez6;                       //�������ȣ           
	char crctn_qtyz12                     [ 12];	char _crctn_qtyz12;                       //��������             
	char crctn_pricez10                   [ 10];	char _crctn_pricez10;                     //�����ܰ�             
} Tc8103OutBlock;

typedef struct tagc8103
{
	Tc8103InBlock                     c8103inblock                          ;  //�⺻�Է� 
	Tc8103OutBlock                    c8103outblock                         ;  //ȭ����� 
} Tc8103;

typedef struct tagc8104InBlock    //�⺻�Է�
{
	char pswd_noz8                        [ 44];	char _pswd_noz8;                          //��й�ȣ             
	char issue_codez6                     [  6];	char _issue_codez6;                       //�����ȣ             
	char canc_qtyz12                      [ 12];	char _canc_qtyz12;                        //��Ҽ���             
	char orgnl_order_noz10                [ 10];	char _orgnl_order_noz10;                  //���ֹ���ȣ           
	char all_part_typez1                  [  1];	char _all_part_typez1;                    //��ұ���             
	char trad_pswd_no_1z8                 [ 44];	char _trad_pswd_no_1z8;                   //�ŷ���й�ȣ1        
	char trad_pswd_no_2z8                 [ 44];	char _trad_pswd_no_2z8;                   //�ŷ���й�ȣ2        
} Tc8104InBlock;

typedef struct tagc8104OutBlock    //ȭ�����
{
	char orgnl_order_noz10                [ 10];	char _orgnl_order_noz10;                  //���ֹ���ȣ           
	char order_noz10                      [ 10];	char _order_noz10;                        //�ֹ���ȣ             
	char mom_order_noz10                  [ 10];	char _mom_order_noz10;                    //���ֹ���ȣ           
	char issue_codez6                     [  6];	char _issue_codez6;                       //�������ȣ           
	char canc_qtyz12                      [ 12];	char _canc_qtyz12;                        //��Ҽ���             
} Tc8104OutBlock;

typedef struct tagc8104
{
	Tc8104InBlock                     c8104inblock                          ;  //�⺻�Է� 
	Tc8104OutBlock                    c8104outblock                         ;  //ȭ����� 
} Tc8104;

typedef struct tagc8141InBlock    //�⺻�Է�
{
	char pswd_noz8                        [ 44];	char _pswd_noz8;                          //��й�ȣ             
	char issue_codez12                    [ 12];	char _issue_codez12;                      //�����ȣ             
	char buy_datez8                       [  8];	char _buy_datez8;                         //�ż�����             
	char order_qtyz12                     [ 12];	char _order_qtyz12;                       //�ֹ�����             
	char order_unit_pricez10              [ 10];	char _order_unit_pricez10;                //�ֹ��ܰ�             
	char trade_typez2                     [  2];	char _trade_typez2;                       //�Ÿ�����             
	char order_condz1                     [  1];	char _order_condz1;                       //�ֹ�����             
	char shsll_pos_flagz1                 [  1];	char _shsll_pos_flagz1;                   //���ŵ����ɿ���       
	char trad_pswd_no_1z8                 [ 44];	char _trad_pswd_no_1z8;                   //�ŷ���й�ȣ1        
	char trad_pswd_no_2z8                 [ 44];	char _trad_pswd_no_2z8;                   //�ŷ���й�ȣ2        
} Tc8141InBlock;

typedef struct tagc8141OutBlock    //ȭ�����
{
	char order_noz10                      [ 10];	char _order_noz10;                        //�ֹ���ȣ             
	char order_qtyz12                     [ 12];	char _order_qtyz12;                       //�ֹ�����             
	char order_unit_pricez10              [ 10];	char _order_unit_pricez10;                //�ֹ��ܰ�             
} Tc8141OutBlock;

typedef struct tagc8141
{
	Tc8141InBlock                     c8141inblock                          ;  //�⺻�Է� 
	Tc8141OutBlock                    c8141outblock                         ;  //ȭ����� 
} Tc8141;

typedef struct tagc8142InBlock    //�⺻�Է�
{
	char password_noz8                    [ 44];	char _password_noz8;                      //��й�ȣ             
	char issue_codez12                    [ 12];	char _issue_codez12;                      //�����ȣ             
	char order_qtyz12                     [ 12];	char _order_qtyz12;                       //�ֹ�����             
	char order_unit_pricez10              [ 10];	char _order_unit_pricez10;                //�ֹ��ܰ�             
	char trade_typez2                     [  2];	char _trade_typez2;                       //�Ÿ�����             
	char order_condz1                     [  1];	char _order_condz1;                       //�ֹ�����             
	char trad_pswd_no_1z8                 [ 44];	char _trad_pswd_no_1z8;                   //�ŷ���й�ȣ1        
	char trad_pswd_no_2z8                 [ 44];	char _trad_pswd_no_2z8;                   //�ŷ���й�ȣ2        
} Tc8142InBlock;

typedef struct tagc8142OutBlock    //ȭ�����
{
	char order_noz10                      [ 10];	char _order_noz10;                        //�ֹ���ȣ             
	char order_qtyz12                     [ 12];	char _order_qtyz12;                       //�ֹ�����             
	char order_unit_pricez10              [ 10];	char _order_unit_pricez10;                //�ֹ��ܰ�             
} Tc8142OutBlock;

typedef struct tagc8142
{
	Tc8142InBlock                     c8142inblock                          ;  //�⺻�Է� 
	Tc8142OutBlock                    c8142outblock                         ;  //ȭ����� 
} Tc8142;

typedef struct tagc8143InBlock    //�⺻�Է�
{
	char pswd_noz8                        [ 44];	char _pswd_noz8;                          //��й�ȣ             
	char issue_codez12                    [ 12];	char _issue_codez12;                      //�����ȣ             
	char crctn_qtyz12                     [ 12];	char _crctn_qtyz12;                       //��������             
	char crctn_pricez10                   [ 10];	char _crctn_pricez10;                     //�����ܰ�             
	char orgnl_order_noz10                [ 10];	char _orgnl_order_noz10;                  //���ֹ���ȣ           
	char all_part_typez1                  [  1];	char _all_part_typez1;                    //��������             
	char order_condz1                     [  1];	char _order_condz1;                       //�ֹ�����             
	char trad_pswd_no_1z8                 [ 44];	char _trad_pswd_no_1z8;                   //�ŷ���й�ȣ1        
	char trad_pswd_no_2z8                 [ 44];	char _trad_pswd_no_2z8;                   //�ŷ���й�ȣ2        
} Tc8143InBlock;

typedef struct tagc8143OutBlock    //ȭ�����
{
	char orgnl_order_noz10                [ 10];	char _orgnl_order_noz10;                  //���ֹ���ȣ           
	char order_noz10                      [ 10];	char _order_noz10;                        //�ֹ���ȣ             
	char mom_order_noz10                  [ 10];	char _mom_order_noz10;                    //���ֹ���ȣ           
	char af_issue_codez12                 [ 12];	char _af_issue_codez12;                   //�������ȣ           
	char crctn_qtyz12                     [ 12];	char _crctn_qtyz12;                       //��������             
	char crctn_pricez10                   [ 10];	char _crctn_pricez10;                     //�����ܰ�             
} Tc8143OutBlock;

typedef struct tagc8143
{
	Tc8143InBlock                     c8143inblock                          ;  //�⺻�Է� 
	Tc8143OutBlock                    c8143outblock                         ;  //ȭ����� 
} Tc8143;

typedef struct tagc8201InBlock    //�⺻�Է�
{
	char pswd_noz44                       [ 44];	char _pswd_noz44;                         //��й�ȣ             
	char bnc_bse_cdz1                     [  1];	char _bnc_bse_cdz1;                       //�ܰ���             
} Tc8201InBlock;

typedef struct tagc8201OutBlock    //ȭ�����
{
	char dpsit_amtz16                     [ 16];	char _dpsit_amtz16;                       //������               
	char mrgn_amtz16                      [ 16];	char _mrgn_amtz16;                        //�ſ����ڱ�           
	char mgint_npaid_amtz16               [ 16];	char _mgint_npaid_amtz16;                 //���ڹ̳���           
	char chgm_pos_amtz16                  [ 16];	char _chgm_pos_amtz16;                    //��ݰ��ɱݾ�         
	char cash_mrgn_amtz16                 [ 16];	char _cash_mrgn_amtz16;                   //�������ű�           
	char subst_mgamt_amtz16               [ 16];	char _subst_mgamt_amtz16;                 //������ű�           
	char coltr_ratez6                     [  6];	char _coltr_ratez6;                       //�㺸����             
	char rcble_amtz16                     [ 16];	char _rcble_amtz16;                       //���ݹ̼���           
	char order_pos_csamtz16               [ 16];	char _order_pos_csamtz16;                 //�ֹ����ɾ�           
	char ecn_pos_csamtz16                 [ 16];	char _ecn_pos_csamtz16;                   //ECN�ֹ����ɾ�        
	char nordm_loan_amtz16                [ 16];	char _nordm_loan_amtz16;                  //�̻�ȯ��             
	char etc_lend_amtz16                  [ 16];	char _etc_lend_amtz16;                    //��Ÿ�뿩��           
	char subst_amtz16                     [ 16];	char _subst_amtz16;                       //���ݾ�             
	char sln_sale_amtz16                  [ 16];	char _sln_sale_amtz16;                    //���ִ㺸��           
	char bal_buy_ttamtz16                 [ 16];	char _bal_buy_ttamtz16;                   //���Կ���(�����ջ�)   
	char bal_ass_ttamtz16                 [ 16];	char _bal_ass_ttamtz16;                   //�򰡱ݾ�(�����ջ�)   
	char asset_tot_amtz16                 [ 16];	char _asset_tot_amtz16;                   //���ڻ��(�����ջ�)   
	char actvt_type10                     [ 10];	char _actvt_type10;                       //Ȱ������             
	char lend_amtz16                      [ 16];	char _lend_amtz16;                        //�����               
	char accnt_mgamt_ratez6               [  6];	char _accnt_mgamt_ratez6;                 //�������ű���         
	char sl_mrgn_amtz16                   [ 16];	char _sl_mrgn_amtz16;                     //�ŵ����ű�           
	char pos_csamt1z16                    [ 16];	char _pos_csamt1z16;                      //20%�ֹ����ɱݾ�      
	char pos_csamt2z16                    [ 16];	char _pos_csamt2z16;                      //30%�ֹ����ɱݾ�      
	char pos_csamt3z16                    [ 16];	char _pos_csamt3z16;                      //40%�ֹ����ɱݾ�      
	char pos_csamt4z16                    [ 16];	char _pos_csamt4z16;                      //100%�ֹ����ɱݾ�     
	char dpsit_amtz_d1_16                 [ 16];	char _dpsit_amtz_d1_16;                   //D1������             
	char dpsit_amtz_d2_16                 [ 16];	char _dpsit_amtz_d2_16;                   //D2������             
	char noticez30                        [ 30];	char _noticez30;                          //��������             /*To-be������*/
	char tot_eal_plsz18                   [ 18];	char _tot_eal_plsz18;                     //���򰡼���           
	char pft_rtz15                        [ 15];	char _pft_rtz15;                          //������               
} Tc8201OutBlock;

typedef struct tagc8201OutBlock1    //ȭ�����, [�ݺ�]
{
	char issue_codez6                     [  6];	char _issue_codez6;                       //�����ȣ             
	char issue_namez40                    [ 40];	char _issue_namez40;                      //�����               
	char bal_typez6                       [  6];	char _bal_typez6;                         //�ܰ�����             
	char loan_datez10                     [ 10];	char _loan_datez10;                       //������               
	char bal_qtyz16                       [ 16];	char _bal_qtyz16;                         //�ܰ����             
	char unstl_qtyz16                     [ 16];	char _unstl_qtyz16;                       //�̰�����             
	char slby_amtz16                      [ 16];	char _slby_amtz16;                        //��ո��԰�           
	char prsnt_pricez16                   [ 16];	char _prsnt_pricez16;                     //���簡               
	char lsnpf_amtz16                     [ 16];	char _lsnpf_amtz16;                       //����(õ��)           
	char earn_ratez9                      [  9];	char _earn_ratez9;                        //������               
	char mrgn_codez4                      [  4];	char _mrgn_codez4;                        //�ſ�����             
	char jan_qtyz16                       [ 16];	char _jan_qtyz16;                         //�ܷ�                 
	char expr_datez10                     [ 10];	char _expr_datez10;                       //������               
	char ass_amtz16                       [ 16];	char _ass_amtz16;                         //�򰡱ݾ�             
	char issue_mgamt_ratez6               [  6];	char _issue_mgamt_ratez6;                 //�������ű���         /*float->char*/
	char medo_slby_amtz16                 [ 16];	char _medo_slby_amtz16;                   //��ոŵ���           
	char post_lsnpf_amtz16                [ 16];	char _post_lsnpf_amtz16;                  //�ŵ�����             
} Tc8201OutBlock1;

typedef struct tagc8201
{
	Tc8201InBlock                     c8201inblock                          ;  //�⺻�Է� 
	Tc8201OutBlock                    c8201outblock                         ;  //ȭ����� 
	Tc8201OutBlock1                   c8201outblock1                   [ 20];  //ȭ����� , [�ݺ�]
} Tc8201;

typedef struct tags8120InBlock    //�⺻�Է�
{
	char inq_gubunz1                      [  1];	char _inq_gubunz1;                        //��ȸ��ü����         
	char pswd_noz8                        [ 44];	char _pswd_noz8;                          //��й�ȣ             
	char group_noz4                       [  4];	char _group_noz4;                         //�׷��ȣ             
	char mkt_slctz1                       [  1];	char _mkt_slctz1;                         //���屸��             
	char order_datez8                     [  8];	char _order_datez8;                       //�ֹ�����             
	char issue_codez12                    [ 12];	char _issue_codez12;                      //�����ȣ             
	char comm_order_typez2                [  2];	char _comm_order_typez2;                  //��ü����             
	char conc_gubunz1                     [  1];	char _conc_gubunz1;                       //ü�ᱸ��             
	char inq_seq_gubunz1                  [  1];	char _inq_seq_gubunz1;                    //��ȸ����             
	char sort_gubunz1                     [  1];	char _sort_gubunz1;                       //���ı���             
	char sell_buy_typez1                  [  1];	char _sell_buy_typez1;                    //�ż�������           
	char mrgn_typez1                      [  1];	char _mrgn_typez1;                        //�ſ뱸��             
	char accnt_admin_typez1               [  1];	char _accnt_admin_typez1;                 //���±���             
	char order_noz10                      [ 10];	char _order_noz10;                        //�ֹ���ȣ             
	char ctsz56                           [ 56];	char _ctsz56;                             //CTS                  
	char trad_pswd1z8                     [ 44];	char _trad_pswd1z8;                       //�ŷ���й�ȣ1        
	char trad_pswd2z8                     [ 44];	char _trad_pswd2z8;                       //�ŷ���й�ȣ2        
	char IsPageUp                         [  1];	char _IsPageUp;                           //ISPAGEUP             
} Ts8120InBlock;

typedef struct tags8120OutBlock    //ȭ�����
{
	char emp_kor_namez20                  [ 20];	char _emp_kor_namez20;                    //�ѱۻ������         
	char brch_namez30                     [ 30];	char _brch_namez30;                       //�ѱ�������           
	char buy_conc_qtyz14                  [ 14];	char _buy_conc_qtyz14;                    //�ż�ü�����         
	char buy_conc_amtz19                  [ 19];	char _buy_conc_amtz19;                    //�ż�ü��ݾ�         
	char sell_conc_qtyz14                 [ 14];	char _sell_conc_qtyz14;                   //�ŵ�ü�����         
	char sell_conc_amtz19                 [ 19];	char _sell_conc_amtz19;                   //�ŵ�ü��ݾ�         
} Ts8120OutBlock;

typedef struct tags8120OutBlock1    //ȭ�����1, [�ݺ�]
{
	char order_datez8                     [  8];	char _order_datez8;                       //�ֹ�����             
	char order_noz10                      [ 10];	char _order_noz10;                        //�ֹ���ȣ             
	char orgnl_order_noz10                [ 10];	char _orgnl_order_noz10;                  //���ֹ���ȣ           
	char accnt_noz11                      [ 11];	char _accnt_noz11;                        //���¹�ȣ             
	char accnt_namez20                    [ 20];	char _accnt_namez20;                      //���¸�               
	char order_kindz20                    [ 20];	char _order_kindz20;                      //�ֹ�����             
	char trd_gubun_noz1                   [  1];	char _trd_gubun_noz1;                     //�Ÿű��й�ȣ         
	char trd_gubunz20                     [ 20];	char _trd_gubunz20;                       //�Ÿű���             
	char trade_type_noz1                  [  1];	char _trade_type_noz1;                    //�ŷ����й�ȣ         
	char trade_type1z20                   [ 20];	char _trade_type1z20;                     //�ŷ�����             
	char issue_codez12                    [ 12];	char _issue_codez12;                      //�����ȣ             
	char issue_namez40                    [ 40];	char _issue_namez40;                      //�����               
	char order_qtyz10                     [ 10];	char _order_qtyz10;                       //�ֹ�����             
	char conc_qtyz10                      [ 10];	char _conc_qtyz10;                        //ü�����             
	char order_unit_pricez12              [ 12];	char _order_unit_pricez12;                //�ֹ��ܰ�             
	char conc_unit_pricez12               [ 12];	char _conc_unit_pricez12;                 //ü����մܰ�         
	char crctn_canc_qtyz10                [ 10];	char _crctn_canc_qtyz10;                  //������Ҽ���         
	char cfirm_qtyz10                     [ 10];	char _cfirm_qtyz10;                       //Ȯ�μ���             
	char media_namez12                    [ 12];	char _media_namez12;                      //��ü����             
	char proc_emp_noz5                    [  5];	char _proc_emp_noz5;                      //ó�����             
	char proc_timez8                      [  8];	char _proc_timez8;                        //ó���ð�             
	char proc_termz8                      [  8];	char _proc_termz8;                        //ó���ܸ�             
	char proc_typez12                     [ 12];	char _proc_typez12;                       //ó������             
	char rejec_codez5                     [  5];	char _rejec_codez5;                       //�ź��ڵ�             
	char avail_qtyz10                     [ 10];	char _avail_qtyz10;                       //���밡�ɼ���         
	char mkt_typez1                       [  1];	char _mkt_typez1;                         //���屸��             
	char shsll_typez20                    [ 20];	char _shsll_typez20;                      //���ŵ�����           
	char passwd_noz8                      [  8];	char _passwd_noz8;                        //��й�ȣ             
} Ts8120OutBlock1;

typedef struct tags8120OutBlock_IN    //Button����
{
	char ctsz56                           [ 56];	char _ctsz56;                             //CTS                  
	char nextbutton                       [  1];	char _nextbutton;                         //NEXTBUTTON           
} Ts8120OutBlock_IN;

typedef struct tags8120
{
	Ts8120InBlock                     s8120inblock                          ;  //�⺻�Է� 
	Ts8120OutBlock                    s8120outblock                         ;  //ȭ����� 
	Ts8120OutBlock1                   s8120outblock1                   [ 20];  //ȭ�����1 , [�ݺ�]
	Ts8120OutBlock_IN                 s8120outblock_in                      ;  //Button���� 
} Ts8120;

typedef struct tagp8101InBlock    //�Է�
{
	char pswd_noz8                        [ 44];	char _pswd_noz8;                          //��й�ȣ             
	char gubunz1                          [  1];	char _gubunz1;                            //����                 
} Tp8101InBlock;

typedef struct tagp8101OutBlock    //ȭ�����
{
	char accnt_namez30                    [ 30];	char _accnt_namez30;                      //���¸�               /*��OBM�����������ʴ��׸�*/
} Tp8101OutBlock;

typedef struct tagp8101OutBlock1    //GRID, [�ݺ�]
{
	char gubunz1                          [  1];	char _gubunz1;                            //����                 1:����2:����3:ä��4:����5:ECN����
	char gubun_namez6                     [  6];	char _gubun_namez6;                       //���и�               
	char issue_codez12                    [ 12];	char _issue_codez12;                      //�����ڵ�             
	char issue_namez30                    [ 30];	char _issue_namez30;                      //�����               
	char mrgn_typez10                     [ 10];	char _mrgn_typez10;                       //�ſ뱸��             
	char lend_datez10                     [ 10];	char _lend_datez10;                       //��������             
	char taxtn_typez10                    [ 10];	char _taxtn_typez10;                      //��������             
	char bal_qtyz12                       [ 12];	char _bal_qtyz12;                         //�ܰ����             
	char sell_rcble_qtyz12                [ 12];	char _sell_rcble_qtyz12;                  //�ŵ��̰���           
	char buy_rcble_qtyz12                 [ 12];	char _buy_rcble_qtyz12;                   //�ż��̰���           
	char sell_psqtyz12                    [ 12];	char _sell_psqtyz12;                      //�ŵ����ɼ���         
	char today_sell_rcble_qz12            [ 12];	char _today_sell_rcble_qz12;              //���ϸŵ���ü�����   
	char avrg_purch_uprc                  [ 10];	char _avrg_purch_uprc;                    //���Դܰ�             
} Tp8101OutBlock1;

typedef struct tagp8101
{
	Tp8101InBlock                     p8101inblock                          ;  //�Է� 
	Tp8101OutBlock                    p8101outblock                         ;  //ȭ����� 
	Tp8101OutBlock1                   p8101outblock1                   [ 17];  //GRID , [�ݺ�]
} Tp8101;

typedef struct tagp8105InBlock    //�Է�
{
	char pwdz8                            [ 44];	char _pwdz8;                              //��й�ȣ             
	char ost_dit_cdz1                     [  1];	char _ost_dit_cdz1;                       //�����ڵ�             /*1����2:�ſ�3:�����ڱݴ���*/
	char sby_dit_cdz1                     [  1];	char _sby_dit_cdz1;                       //�Ÿű����ڵ�         /*1:�ŵ���ȯ2:�ż��ű�*/
	char iem_gbz1                         [  1];	char _iem_gbz1;                           //���񱸺�             /*1:�ֽ�2:ELW3:�����μ�4:��Ÿ*/
	char iem_cdz12                        [ 12];	char _iem_cdz12;                          //�����ڵ�             
	char nmn_pr_tp_gbz1                   [  1];	char _nmn_pr_tp_gbz1;                     //ȣ����������         /*1:��ȣ������-1�ڸ�2:�Žý���ȣ������-2�ڸ�*/
	char nmn_pr_tp_cdz2                   [  2];	char _nmn_pr_tp_cdz2;                     //ȣ�������ڵ�         /*01:����05:���尡06:���Ǻ�10:S-OPTION�ڱ�11:������Ź12:������13:�ֿ켱61:�����ð�71:���Ľð�81:�Ű��ܴ���*/
	char orr_prz18                        [ 18];	char _orr_prz18;                          //�ֹ�����             
	char mdi_tp_cdz1                      [  1];	char _mdi_tp_cdz1;                        //��ü�����ڵ�         /*1:����2:HTS3:�����ARS4:����������5:TXflat6:TXLever7:TXLever����ſ�8:TXWin9:TXWinSMIT0:TX�ٷ�*/
	char cfd_lon_cdz2                     [  2];	char _cfd_lon_cdz2;                       //�ſ�����ڵ�         /*01:����02:����03:����04:�ڴ�*/
	char lon_dtz8                         [  8];	char _lon_dtz8;                           //��������             
} Tp8105InBlock;

typedef struct tagp8105OutBlock    //ȭ�����
{
	char dcaz18                           [ 18];	char _dcaz18;                             //������               /*���Ͽ�����*/
	char nxt_dd_dcaz18                    [ 18];	char _nxt_dd_dcaz18;                      //���Ͽ�����           /*D+1������*/
	char nxt2_dd_dcaz18                   [ 18];	char _nxt2_dd_dcaz18;                     //�����Ͽ�����         /*D+2������*/
	char max_pbl_amtz18                   [ 18];	char _max_pbl_amtz18;                     //�ִ밡�ɱݾ�         /*�̼����ɱݾ�*/
	char max_pbl_qtyz18                   [ 18];	char _max_pbl_qtyz18;                     //�ִ밡�ɼ���         /*�̼����ɼ���*/
	char rvb_orn_max_pbl_feez18           [ 18];	char _rvb_orn_max_pbl_feez18;             //�̼��߻��ִ밡�ɼ����� /*�̼�������*/
	char csh_orr_pbl_amtz18               [ 18];	char _csh_orr_pbl_amtz18;                 //�����ֹ����ɱݾ�     /*���ݰ��ɱݾ�*/
	char csh_orr_pbl_qtyz18               [ 18];	char _csh_orr_pbl_qtyz18;                 //�����ֹ����ɼ���     /*���ݰ��ɼ���*/
	char ost_fee1z18                      [ 18];	char _ost_fee1z18;                        //���ݼ�����           /*���ݼ�����*/
	char cfd_rvb_orr_pbl_amtz18           [ 18];	char _cfd_rvb_orr_pbl_amtz18;             //�ſ�̼��ֹ����ɱݾ� /*�ſ�̼����ɱݾ�*/
	char cfd_rvb_orr_pbl_qtyz18           [ 18];	char _cfd_rvb_orr_pbl_qtyz18;             //�ſ�̼��ֹ����ɼ��� /*�ſ�̼����ɼ���*/
	char cfd_max_pbl_feez18               [ 18];	char _cfd_max_pbl_feez18;                 //�ſ��ִ밡�ɼ�����   /*�ſ�̼�������*/
	char cfd_orr_pbl_amtz18               [ 18];	char _cfd_orr_pbl_amtz18;                 //�ſ��ֹ����ɱݾ�     /*�ſ�̹߻����ɱݾ�*/
	char cfd_orr_pbl_qtyz18               [ 18];	char _cfd_orr_pbl_qtyz18;                 //�ſ��ֹ����ɼ���     /*�ſ�̹߻����ɼ���*/
	char ost_fee2z18                      [ 18];	char _ost_fee2z18;                        //������2              /*�ſ�̹߻�������*/
	char sdr_xps1z18                      [ 18];	char _sdr_xps1z18;                        //�����1              
	char sdr_xpsz18                       [ 18];	char _sdr_xpsz18;                         //�����               
} Tp8105OutBlock;

typedef struct tagp8105
{
	Tp8105InBlock                     p8105inblock                          ;  //�Է� 
	Tp8105OutBlock                    p8105outblock                         ;  //ȭ����� 
} Tp8105;

typedef struct tagp8104InBlock    //�⺻�Է�
{
	char pswd_noz8                        [ 44];	char _pswd_noz8;                          //��й�ȣ             
	char issue_codez6                     [  6];	char _issue_codez6;                       //�����ڵ�             
	char gubunz1                          [  1];	char _gubunz1;                            //����                 
	char the_datez8                       [  8];	char _the_datez8;                         //������               /*��OBM�����������ʴ��׸�*/
} Tp8104InBlock;

typedef struct tagp8104OutBlock    //ȭ�����
{
	char issue_codez6                     [  6];	char _issue_codez6;                       //�����ڵ�             
	char order_qtyz12                     [ 12];	char _order_qtyz12;                       //�ŵ����ɼ���         
} Tp8104OutBlock;

typedef struct tagp8104
{
	Tp8104InBlock                     p8104inblock                          ;  //�⺻�Է� 
	Tp8104OutBlock                    p8104outblock                         ;  //ȭ����� 
} Tp8104;








////////////////////////////////////////
//	�����ɼ�
////////////////////////////////////////

typedef struct tags8301InBlock    //�⺻�Է�
{
	char slbuy_typez1                     [  1];	char _slbuy_typez1;                       //�ż��ŵ�����         
	char passwd_noz8                      [ 44];	char _passwd_noz8;                        //��й�ȣ             
	char issue_codez9                     [  9];	char _issue_codez9;                       //�����ڵ�             
	char ord_typez1                       [  1];	char _ord_typez1;                         //�ֹ�����             
	char trade_typez1                     [  1];	char _trade_typez1;                       //�ŷ�����             
	char order_qtyz8                      [  8];	char _order_qtyz8;                        //�ֹ�����             
	char order_pricez12                   [ 12];	char _order_pricez12;                     //�ֹ�����             
	char trad_pswd_no_1z8                 [ 44];	char _trad_pswd_no_1z8;                   //�ŷ���й�ȣ1        
	char trad_pswd_no_2z8                 [ 44];	char _trad_pswd_no_2z8;                   //�ŷ���й�ȣ2        
} Ts8301InBlock;

typedef struct tags8301OutBlock    //ȭ�����
{
	char order_qtyz8                      [  8];	char _order_qtyz8;                        //�ֹ�����             
	char order_pricez12                   [ 12];	char _order_pricez12;                     //�ֹ�����             
	char order_noz10                      [ 10];	char _order_noz10;                        //�ֹ���ȣ             
	char ord_pos_csamtz16                 [ 16];	char _ord_pos_csamtz16;                   //�ֹ���������         
	char ord_pos_ttamtz16                 [ 16];	char _ord_pos_ttamtz16;                   //�ֹ������Ѿ�         
	char ord_insuf_csamtz16               [ 16];	char _ord_insuf_csamtz16;                 //�ֹ���������         
	char ord_insuf_ttamtz16               [ 16];	char _ord_insuf_ttamtz16;                 //�ֹ������Ѿ�         
	char ord_pos_qtyz16                   [ 16];	char _ord_pos_qtyz16;                     //�ֹ����ɼ���         
} Ts8301OutBlock;

typedef struct tags8301
{
	Ts8301InBlock                     s8301inblock                          ;  //�⺻�Է� 
	Ts8301OutBlock                    s8301outblock                         ;  //ȭ����� 
} Ts8301;


typedef struct tags8302InBlock    //�⺻�Է�
{
	char gubunz1                          [  1];	char _gubunz1;                            //����/��ұ���        
	char slbuy_typez1                     [  1];	char _slbuy_typez1;                       //�ż��ŵ�����         
	char pswd_noz8                        [ 44];	char _pswd_noz8;                          //��й�ȣ             
	char orgnl_order_noz10                [ 10];	char _orgnl_order_noz10;                  //���ֹ���ȣ           
	char issue_codez9                     [  9];	char _issue_codez9;                       //�����ڵ�             
	char orgnl_ord_typez1                 [  1];	char _orgnl_ord_typez1;                   //���ֹ�����           
	char crctn_ord_typez1                 [  1];	char _crctn_ord_typez1;                   //�����ֹ�����         
	char order_qtyz8                      [  8];	char _order_qtyz8;                        //�ֹ�����             
	char order_pricez12                   [ 12];	char _order_pricez12;                     //�ֹ�����             
	char trad_pswd_no_1z8                 [ 44];	char _trad_pswd_no_1z8;                   //�ŷ���й�ȣ1        
	char trad_pswd_no_2z8                 [ 44];	char _trad_pswd_no_2z8;                   //�ŷ���й�ȣ2        
} Ts8302InBlock;

typedef struct tags8302OutBlock    //ȭ�����
{
	char order_noz10                      [ 10];	char _order_noz10;                        //�ֹ���ȣ             
	char ord_pos_csamtz16                 [ 16];	char _ord_pos_csamtz16;                   //�ֹ���������         
	char ord_pos_ttamtz16                 [ 16];	char _ord_pos_ttamtz16;                   //�ֹ������Ѿ�         
	char ord_insuf_csamtz16               [ 16];	char _ord_insuf_csamtz16;                 //�ֹ���������         
	char ord_insuf_ttamtz16               [ 16];	char _ord_insuf_ttamtz16;                 //�ֹ������Ѿ�         
	char ord_pos_qtyz16                   [ 16];	char _ord_pos_qtyz16;                     //�ֹ����ɼ���         
	char order_qtyz8                      [  8];	char _order_qtyz8;                        //�ֹ�����             
	char order_pricez12                   [ 12];	char _order_pricez12;                     //�ֹ�����             
} Ts8302OutBlock;

typedef struct tags8302
{
	Ts8302InBlock                     s8302inblock                          ;  //�⺻�Է� 
	Ts8302OutBlock                    s8302outblock                         ;  //ȭ����� 
} Ts8302;

typedef struct tagc8311InBlock    //�Է�
{
	char in_pswdz8                        [ 44];	char _in_pswdz8;                          //��й�ȣ             
	char job_gubunz1                      [  1];	char _job_gubunz1;                        //����                 
	char trobj_stock_codez12              [ 12];	char _trobj_stock_codez12;                //����ڻ��ڵ�         /*������*/
} Tc8311InBlock;

typedef struct tagc8311OutBlock    //ȭ�����
{
	char out_acnamez30                    [ 30];	char _out_acnamez30;                      //���¸�               
	char out_ttamtz14                     [ 14];	char _out_ttamtz14;                       //��Ź�Ѿ�             
	char out_cashz14                      [ 14];	char _out_cashz14;                        //��Ź����             
	char out_mrgn_ttamtz14                [ 14];	char _out_mrgn_ttamtz14;                  //���ű��Ѿ�           
	char out_mrgn_cashz14                 [ 14];	char _out_mrgn_cashz14;                   //���ű�����           
	char out_order_ttamtz14               [ 14];	char _out_order_ttamtz14;                 //�ֹ������Ѿ�         
	char out_order_cashz14                [ 14];	char _out_order_cashz14;                  //�ֹ���������         
	char out_tot_ttamtz14                 [ 14];	char _out_tot_ttamtz14;                   //�����Ѿ�           
	char out_tot_cashz14                  [ 14];	char _out_tot_cashz14;                    //��������           
	char out_substz14                     [ 14];	char _out_substz14;                       //���ݾ�             
	char out_renewz14                     [ 14];	char _out_renewz14;                       //��������             
	char out_stlmtz14                     [ 14];	char _out_stlmtz14;                       //��������             
	char out_opt_sellz14                  [ 14];	char _out_opt_sellz14;                    //�ɼǸŵ����         
	char out_opt_buyz14                   [ 14];	char _out_opt_buyz14;                     //�ɼǸż����         
	char out_opt_valuez14                 [ 14];	char _out_opt_valuez14;                   //�ɼ��򰡱ݾ�         
	char out_pred_substz14                [ 14];	char _out_pred_substz14;                  //���ϴ��ŵ�         
	char out_thday_substz14               [ 14];	char _out_thday_substz14;                 //���ϴ��ŵ�         
	char out_pred_amtz14                  [ 14];	char _out_pred_amtz14;                    //���ϰ��Ա�           
	char out_opt_hangz14                  [ 14];	char _out_opt_hangz14;                    //�ɼ����ݾ�         
	char out_opt_baiz14                   [ 14];	char _out_opt_baiz14;                     //�ɼǹ����ݾ�         
	char out_thday_amtz14                 [ 14];	char _out_thday_amtz14;                   //���ϰ��Ա�           
	char out_rcblez14                     [ 14];	char _out_rcblez14;                       //�̼���               
	char out_ovamtz14                     [ 14];	char _out_ovamtz14;                       //��ü��               
	char out_ftr_cmsnz14                  [ 14];	char _out_ftr_cmsnz14;                    //����������           
	char out_opt_cmsnz14                  [ 14];	char _out_opt_cmsnz14;                    //�ɼǼ�����           
	char out_afterz14                     [ 14];	char _out_afterz14;                       //�����̿��           
	char out_asset_ttamtz14               [ 14];	char _out_asset_ttamtz14;                 //���ڻ��Ѿ�           
	char out_asset_ttcashz14              [ 14];	char _out_asset_ttcashz14;                //���ڻ�����           
} Tc8311OutBlock;

typedef struct tagc8311OutBlock1    //���, [�ݺ�]
{
	char out_issuez9                      [  9];	char _out_issuez9;                        //�����ڵ�             
	char out_isnamez30                    [ 30];	char _out_isnamez30;                      //�����               
	char out_slbyz6                       [  6];	char _out_slbyz6;                         //�Ÿű���             
	char out_qtyz14                       [ 14];	char _out_qtyz14;                         //����                 
	char out_averz12                      [ 12];	char _out_averz12;                        //��հ�               
	char out_pricez12                     [ 12];	char _out_pricez12;                       //���簡               
	char out_lsnpfz14                     [ 14];	char _out_lsnpfz14;                       //�򰡼���             
	char today_revs_odqtyz12              [ 12];	char _today_revs_odqtyz12;                //�ֹ�����             
	char sell_posbl_qtyz12                [ 12];	char _sell_posbl_qtyz12;                  //û�갡�ɼ���         
} Tc8311OutBlock1;

typedef struct tagc8311
{
	Tc8311InBlock                     c8311inblock                          ;  //�Է� 
	Tc8311OutBlock                    c8311outblock                         ;  //ȭ����� 
	Tc8311OutBlock1                   c8311outblock1                   [ 10];  //��� , [�ݺ�]
} Tc8311;

typedef struct tagc8322InBlock    //�⺻�Է�
{
	char pswd_noz8                        [ 44];	char _pswd_noz8;                          //��й�ȣ             
	char order_datez8                     [  8];	char _order_datez8;                       //�ֹ�����             
	char issue_codez9                     [  9];	char _issue_codez9;                       //�����ȣ             
	char conc_gubunz1                     [  1];	char _conc_gubunz1;                       //ü�ᱸ��             0:��ü1:��ü��2:ü��
	char sort_gubunz1                     [  1];	char _sort_gubunz1;                       //���ı���             0:�ֹ���ȣ��1:�ֹ���ȣ����
	char sl_buy_typez1                    [  1];	char _sl_buy_typez1;                      //�ż�������           0:��ü1:�ŵ�2:�ż�
	char issue_gubunz1                    [  1];	char _issue_gubunz1;                      //���񱸺�             0:��ü1:����2:�ɼ�
	char disp_gubunz1                     [  1];	char _disp_gubunz1;                       //��ȸ����             1:�ֹ��ð���2:ü��ð���
	char cts_areaz67                      [ 76];	char _cts_areaz67;                        //CTS                  
	char trad_pswd1z8                     [ 44];	char _trad_pswd1z8;                       //�ŷ���й�ȣ1        
	char trad_pswd2z8                     [ 44];	char _trad_pswd2z8;                       //�ŷ���й�ȣ2        
	char IsPageUp                         [  1];	char _IsPageUp;                           //ISPAGEUP             
} Tc8322InBlock;

typedef struct tagc8322OutBlock    //ȭ�����
{
	char order_datez8                     [  8];	char _order_datez8;                       //�ֹ�����             
	char accnt_namez40                    [ 40];	char _accnt_namez40;                      //���¸�               
} Tc8322OutBlock;

typedef struct tagc8322OutBlock1    //ȭ�����1, [�ݺ�]
{
	char order_noz10                      [ 10];	char _order_noz10;                        //�ֹ���ȣ             
	char orgnl_order_noz10                [ 10];	char _orgnl_order_noz10;                  //���ֹ���ȣ           
	char conc_noz6                        [  6];	char _conc_noz6;                          //ü���ȣ             
	char order_datez8                     [  8];	char _order_datez8;                       //�ֹ�����             
	char slbuy_typez10                    [ 10];	char _slbuy_typez10;                      //�ֹ�����             
	char slby_typez15                     [ 15];	char _slby_typez15;                       //�Ÿű���             
	char issue_codez9                     [  9];	char _issue_codez9;                       //�����ȣ             
	char issue_namez40                    [ 40];	char _issue_namez40;                      //�����               
	char order_qtyz12                     [ 12];	char _order_qtyz12;                       //�ֹ�����             
	char order_pricez12                   [ 12];	char _order_pricez12;                     //�ֹ��ܰ�             
	char conc_qtyz12                      [ 12];	char _conc_qtyz12;                        //ü�����             
	char index_conc_pricez12              [ 12];	char _index_conc_pricez12;                //ü����մܰ�         
	char unconc_qtyz12                    [ 12];	char _unconc_qtyz12;                      //��ü�����           
	char rqst_typez6                      [  6];	char _rqst_typez6;                        //ó������             
	char rqst_timez8                      [  8];	char _rqst_timez8;                        //ó���ð�             
} Tc8322OutBlock1;

typedef struct tagc8322OutBlock_IN    //Button����
{
	char cts_areaz67                      [ 76];	char _cts_areaz67;                        //CTS                  
	char nextbutton                       [  1];	char _nextbutton;                         //NEXTBUTTON           
} Tc8322OutBlock_IN;

typedef struct tagc8322
{
	Tc8322InBlock                     c8322inblock                          ;  //�⺻�Է� 
	Tc8322OutBlock                    c8322outblock                         ;  //ȭ����� 
	Tc8322OutBlock1                   c8322outblock1                   [ 20];  //ȭ�����1 , [�ݺ�]
	Tc8322OutBlock_IN                 c8322outblock_in                      ;  //Button���� 
} Tc8322;

typedef struct tagp8301InBlock    //�Է�
{
	char issue_codez9                     [  9];	char _issue_codez9;                       //�����ڵ�             
	char slbuy_typez1                     [  1];	char _slbuy_typez1;                       //�Ÿű���             
	char ord_typez1                       [  1];	char _ord_typez1;                         //�ֹ�����             
	char order_pricez12                   [ 12];	char _order_pricez12;                     //�ֹ��ܰ�             
	char passwd_noz8                      [ 44];	char _passwd_noz8;                        //��й�ȣ             
} Tp8301InBlock;

typedef struct tagp8301OutBlock    //ȭ�����
{
	char accnt_namez20                    [ 20];	char _accnt_namez20;                      //���¸�               
	char kor_issue_namez40                [ 40];	char _kor_issue_namez40;                  //�����               
	char be_dpsit_ttamtz14                [ 14];	char _be_dpsit_ttamtz14;                  //�ֹ���               
	char be_dpsit_cash_amtz14             [ 14];	char _be_dpsit_cash_amtz14;               //�ֹ���               
	char be_brkrg_mrgn_ttamz14            [ 14];	char _be_brkrg_mrgn_ttamz14;              //�ֹ���               
	char be_brkrg_cash_mgamz14            [ 14];	char _be_brkrg_cash_mgamz14;              //�ֹ���               
	char be_order_pos_ttamtz14            [ 14];	char _be_order_pos_ttamtz14;              //�ֹ���               
	char be_order_pos_csamtz14            [ 14];	char _be_order_pos_csamtz14;              //�ֹ���               
	char af_dpsit_ttamtz14                [ 14];	char _af_dpsit_ttamtz14;                  //�ֹ���               
	char af_dpsit_cash_amtz14             [ 14];	char _af_dpsit_cash_amtz14;               //�ֹ���               
	char af_brkrg_mrgn_ttamz14            [ 14];	char _af_brkrg_mrgn_ttamz14;              //�ֹ���               
	char af_brkrg_cash_mgamz14            [ 14];	char _af_brkrg_cash_mgamz14;              //�ֹ���               
	char af_order_pos_ttamtz14            [ 14];	char _af_order_pos_ttamtz14;              //�ֹ���               
	char af_order_pos_csamtz14            [ 14];	char _af_order_pos_csamtz14;              //�ֹ���               
	char new_pos_qtyz14                   [ 14];	char _new_pos_qtyz14;                     //�ű��ֹ�             
	char bal_pos_qtyz14                   [ 14];	char _bal_pos_qtyz14;                     //�ܰ��ֹ�             
	char tot_pos_qtyz14                   [ 14];	char _tot_pos_qtyz14;                     //TOTAL                
} Tp8301OutBlock;

typedef struct tagp8301
{
	Tp8301InBlock                     p8301inblock                          ;  //�Է� 
	Tp8301OutBlock                    p8301outblock                         ;  //ȭ����� 
} Tp8301;

typedef struct tagp8302InBlock    //�Է�
{
	char proc_gubunz1                     [  1];	char _proc_gubunz1;                       //ó������             
	char trobj_stock_codez12              [ 12];	char _trobj_stock_codez12;                //����ڻ��ڵ�         
} Tp8302InBlock;

typedef struct tagp8302OutBlock    //ȭ�����
{
	char o_accnt_namez40                  [ 40];	char _o_accnt_namez40;                    //���¸�               
} Tp8302OutBlock;

typedef struct tagp8302OutBlock1    //���¸�, [�ݺ�]
{
	char index_issue_codez9               [  9];	char _index_issue_codez9;                 //����                 
	char index_issue_namez30              [ 30];	char _index_issue_namez30;                //�����               
	char index_slbuy_typez2               [  2];	char _index_slbuy_typez2;                 //�Ÿű���             
	char index_slbuy_namez6               [  6];	char _index_slbuy_namez6;                 //�Ÿű��и�           
	char bal_qtyz12                       [ 12];	char _bal_qtyz12;                         //�ܰ����             
	char today_revs_odqtyz12              [ 12];	char _today_revs_odqtyz12;                //�ֹ�����             
	char sell_posbl_qtyz12                [ 12];	char _sell_posbl_qtyz12;                  //û�갡�ɼ���         
	char avrgez14                         [ 14];	char _avrgez14;                           //��հ�               
} Tp8302OutBlock1;

typedef struct tagp8302
{
	Tp8302InBlock                     p8302inblock                          ;  //�Է� 
	Tp8302OutBlock                    p8302outblock                         ;  //ȭ����� 
	Tp8302OutBlock1                   p8302outblock1                   [ 20];  //���¸� , [�ݺ�]
} Tp8302;








////////////////////////////////////////
//	�ǽð� ��Ŷ
////////////////////////////////////////

typedef struct tagd2OutBlock    //���
{
	char userid                           [  8];   //�����ID             
	char itemgb                           [  1];   //ITEM����             
	char accountno                        [ 11];   //���¹�ȣ             
	char orderno                          [ 10];   //�ֹ���ȣ             
	char issuecd                          [ 15];   //�����ڵ�             
	char slbygb                           [  1];   //�ŵ�������           
	char concgty                          [ 10];   //ü�����             
	char concprc                          [ 11];   //ü�ᰡ��             
	char conctime                         [  6];   //ü��ð�             
	char ucgb                             [  1];   //������ұ���         
	char rejgb                            [  1];   //�źα���             
	char fundcode                         [  3];   //�ݵ��ڵ�             
	char sin_gb                           [  2];   //�ſ뱸��             
	char loan_date                        [  8];   //��������             
	char ato_ord_tpe_chg                  [  1];   //�����ɼ��ֹ��������濩��             
	char filler                           [ 34];   //filler           
} Td2OutBlock;

typedef struct tagd3OutBlock    //���
{
	char userid                           [  8];   //USERID               
	char itemgb                           [  1];   //ITEM����             
	char accountno                        [ 11];   //���¹�ȣ             
	char orderno                          [ 10];   //�ֹ���ȣ             
	char orgordno                         [ 10];   //���ֹ���ȣ           
	char ordercd                          [  2];   //�ֹ�����             
	char issuecd                          [ 15];   //�����ڵ�             
	char issuename                        [ 20];   //�����               
	char slbygb                           [  1];   //�Ÿű���             
	char order_type                       [  2];   //�ֹ�����             
	char ordergty                         [ 10];   //�ֹ�����             
	char orderprc                         [ 11];   //�ֹ��ܰ�             
	char procnm                           [  2];   //ó������             
	char commcd                           [  2];   //��ü����             
	char order_cond                       [  1];   //�ֹ�����1            
	char fundcode                         [  3];   //�ݵ��ڵ�             
	char sin_gb                           [  2];   //�ſ뱸��             
	char order_time                       [  6];   //�ֹ��ð�             
	char loan_date                        [  8];   //��������             
} Td3OutBlock;
