NetCan-Soft >> libnetcan-soft.soʹ��˵��
����:
    �ÿ������һЩʵ�õĺ���(�������˵��)�����ṩ�˶�̬��(libnetcan-soft.so)�;�̬��(libnetcan-soft.a)�����ʹ�á�
    �汾: V2.0.9
    ���ص�ַ: http://ncan.ys168.com
ʹ�÷���:
    ������õ��ÿ⺯��������������Ĵ���:
        1.���Ӷ�̬��libnetcan-soft.so (����)
            # gcc -o [PROGRAM] [SOURCES] -lnetcan-soft.so
            # ldd [PROGRAM] (�������libnetcan-soft.so => [LIBDIR]�����ӳɹ�)
            # ./[PROGRAM] (���г���)
        2.���Ӿ�̬��libnetcan-soft.a
            # gcc -o [PROGRAM] [SOURCES] /lib/libnetcan-soft.a -lpthread
            # ldd [PROGRAM] (�ᷢ��û��libnetcan-soft.so�ˣ���������һ��)
            # ./[PROGRAM] (���г���)
��������:
    ע��: �ÿ����к���ִ�гɹ��᷵�ط�0ֵ�����򷵻�0ֵ��
    �ļ�����:
        filebyte():
            ԭ��: int filebyte( FILE * stream );
            ����: �����ļ� stream ��С�����ش�Сֵ(�ֽ�)            
        fline():
            ԭ��: int fline( FILE * stream );
            ����: �����ļ� stream ����������
        filearray():
            ԭ��: int filearray( FILE * stream, char *array, int arraysize);
            ����: ���ļ� stream ����ȫ���Ƶ���СΪ arraysize ������ array �� 
        ftotal():
            ԭ��: int ftotal( DIR * path ); 
            ����: ����Ŀ¼ path �µ��ļ�(Ŀ¼)����������
    ����:
        fcs():
            ԭ��: char * fcs( char * title, char * path, int cs, char * out, int outsize);
            ����: ָ��·�� path ���û�ѡ���ļ�������ļ�������СΪ outdir ������ out ��
            ˵��: �β� title Ϊ�ú����ı���,Ĭ��Ϊ "��(null)"
                  �β� path Ϊ����Ŀ¼,Ĭ��Ϊ��,�븳ֵ
                  �β� cs Ϊѡ��ģʽ,������ֵ 1/2,��Ӧ ��ѡ/��ѡ ,Ĭ��Ϊ ��ѡ(2)
                  �ú���Ϊָ�뺯��,����û�ѡ�� "ѡ��Ŀ¼" �򷵻ظ�Ŀ¼�ĵ�ֵַ
                  ����û�ѡ�����ļ�����ѡ�� "ȷ��" �򷵻ظ�Ŀ¼�ĵ�ֵַ������û�ѡ�����ļ�������СΪ outsize ������ out ��,���� out �е��ļ������ַ� '/' �ֿ�
                  ����û�ѡ�� "����" ����������,����ֵ: "EXIT"
                  ����û���ֹ�ú���,����: "KILL"
            ����: �������� ����,ȷ�� ִ��,���� �л��˵�
                  �����ļ�(���ش���/NetCan-Soft/Settings/fcs_theme.conf)���Զ��� ����/����
        getch():
            ԭ��: int getch(void);
            ����: ����һ���������ؼ�ֵ

����/���µ�ַ: http://ncan.ys168.com
QQ: 1469709759
