
// ˼·���

// EXT ģ�����ƿ��Ի�����һ��functional����������

typedef(time_gt) (*tick_fn)(void);


typedef(gmp_error_t)(functional_gt)(gmp_fp_functional *param);


typedef struct _tag_gmp_fp_functional
{
    // �������һ���Ƿ�������
    // Non-blocking function
    functional_gt callback;

    // parameter for callback
    // ����ͨ���̳й�ϵ��������
    //void *param;

    // last invoke time
    // for time counting and delta-time mode programming
    time_gt last_tick;

    // ���ڵ�
    gmp_function_player *parent;

    // �γ�������������Ӧ����ʲô��ʽ��δ֪��Ŀ������������
    gmp_fp_functional *next;

}gmp_fp_functional;

// utilities for fp_functional type
// 

// ����������ᱻplayer����Ӧ��������
gmp_error_t invoke_fp_functional(gmp_fp_functional *fp_obj)
{
    fp_obj->callback();

    //���½ṹ��������������
}

typedef struct _tag_function_player
{
    // function point to tick get
    tick_fn tick;

    // last invoke time
    time_gt last_tick;

    // list to functional
    vector<gmp_fp_functional> function_pointer_list;

}gmp_function_player;

// ע��һ���µ�functional
