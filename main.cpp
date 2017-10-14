#include<windows.h>
#include<iostream>
#include<cstring>
#include<fstream>
#include<ctime>
#include <sstream>
#include "define.h"

using namespace std;
LRESULT CALLBACK WindowProcedure(HWND,UINT,WPARAM,LPARAM);
LRESULT CALLBACK WindowProcedure1(HWND hWnd1,UINT msg1,WPARAM wp1,LPARAM lp1);
LRESULT CALLBACK WindowProcedure2(HWND hWnd2,UINT msg2,WPARAM wp2,LPARAM lp2);
//global variable.

int open = 0,i,check[15]={0},p1=0,p2=0,c[15],q[15]={0},date_count= -1,count_abs=0;
char output[3][50],file_name[100],remark[50],open_file[50],temp_name[4][20];
char data[400];
char dis[400];
int abs_no[15]={0};
char notation[20] = "..//Attendance_log/";
char date[50][50]={""};

HWND c_handel[32],hdisplay;
HWND hDrop1,hDrop2,hDrop3,hDrop4,hDrop5,hDrop6,hDrop7,hCheckBox1,hCheckBox2,hRe;


// GUI class
class GUI{
HMENU hMenu;
HMENU hMenu1Item,hMenu1Item1,hMenu2Item;
public:

    void get_menu(HWND hWnd){
        //for main menu creation
        hMenu = CreateMenu();
        //for sub item craation
        hMenu1Item = CreateMenu();
        hMenu2Item = CreateMenu();
        //FIle menu tab
        AppendMenu(hMenu,MF_POPUP,(UINT_PTR)hMenu1Item,"File");

        //File menu item
        AppendMenu(hMenu1Item,MF_STRING,Exit,"Exit");
        AppendMenu(hMenu1Item,MF_STRING,view,"View Attendance");
        //help tab
        AppendMenu(hMenu,MF_POPUP,(UINT_PTR)hMenu2Item,"Help");
        SetMenu(hWnd,hMenu);
    }

    void get_elements(HWND hWnd){

        CreateWindow("Static","Select Lecture Details",WS_VISIBLE | WS_CHILD ,35,15,150,100,hWnd,NULL,NULL,NULL);

        //first label
        CreateWindow("Static","Select Class :",WS_VISIBLE | WS_CHILD ,15,55,150,100,hWnd,NULL,NULL,NULL);
        hDrop1 =  CreateWindow("Combobox","",CBS_DROPDOWNLIST | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE,15, 75, 169, 100, hWnd,(HMENU)drop1, NULL,NULL);
        SendMessage(hDrop1,CB_ADDSTRING,1,(LPARAM)"FY iMCA");
        SendMessage(hDrop1,CB_ADDSTRING,2,(LPARAM)"SY iMCA");
        SendMessage(hDrop1,CB_ADDSTRING,3,(LPARAM)"TY iMCA");
        SendMessage(hDrop1,CB_ADDSTRING,4,(LPARAM)"MCA");

        //second label
        CreateWindow("Static","Select Faculty :",WS_VISIBLE | WS_CHILD ,15,120,150,100,hWnd,NULL,NULL,NULL);
        hDrop2 =  CreateWindow("Combobox","",CBS_DROPDOWNLIST | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE,15, 145, 169, 100, hWnd, (HMENU)drop2, NULL,NULL);
        SendMessage(hDrop2,CB_ADDSTRING,1,(LPARAM)"Siddhi Shah");
        SendMessage(hDrop2,CB_ADDSTRING,2,(LPARAM)"Hiral Vegda");
        SendMessage(hDrop2,CB_ADDSTRING,3,(LPARAM)"Pratik Thanawala");
        SendMessage(hDrop2,CB_ADDSTRING,4,(LPARAM)"Kunjal Gajjar");


        //3rd label
        CreateWindow("Static","Select Lecture :",WS_VISIBLE | WS_CHILD ,15,190,150,100,hWnd,NULL,NULL,NULL);
        hDrop3 =  CreateWindow("Combobox","",CBS_DROPDOWNLIST | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE,15, 215, 169, 100, hWnd, (HMENU)drop3, NULL,NULL);
        SendMessage(hDrop3,CB_ADDSTRING,1,(LPARAM)"SAD");
        SendMessage(hDrop3,CB_ADDSTRING,2,(LPARAM)"DSA");
        SendMessage(hDrop3,CB_ADDSTRING,3,(LPARAM)"MS");
        SendMessage(hDrop3,CB_ADDSTRING,4,(LPARAM)"OOCP");


        //button
        CreateWindow("Button","Mark",WS_VISIBLE | WS_CHILD ,75,265,60,25,hWnd,(HMENU)button,NULL,NULL);
    }

    void get_check_box(HWND hWnd){
    // 1 to 15
    //top label
        CreateWindowW(L"Static",L"-- Selected numbers will be mark as absent -- ",WS_VISIBLE | WS_CHILD ,160,10,318,68,hWnd,NULL,NULL,NULL);
        c_handel[1] = CreateWindowW(L"Button",L"1",WS_VISIBLE | WS_CHILD | BS_CHECKBOX ,10,55,26,10, hWnd,(HMENU)ID1, NULL,NULL);
        c_handel[2] = CreateWindowW(L"Button",L"2",WS_VISIBLE | WS_CHILD | BS_CHECKBOX ,50,55,26,10, hWnd,(HMENU)ID2, NULL,NULL);
        c_handel[3] =  CreateWindowW(L"Button",L"3",WS_VISIBLE | WS_CHILD | BS_CHECKBOX ,90,55,26,10, hWnd,(HMENU)ID3, NULL,NULL);
        c_handel[4] =  CreateWindowW(L"Button",L"4",WS_VISIBLE | WS_CHILD | BS_CHECKBOX ,130,55,26,10, hWnd,(HMENU)ID4, NULL,NULL);
        c_handel[5] = CreateWindowW(L"Button",L"5",WS_VISIBLE | WS_CHILD | BS_CHECKBOX ,170,55,26,10, hWnd,(HMENU)ID5, NULL,NULL);
        c_handel[6] = CreateWindowW(L"Button",L"6",WS_VISIBLE | WS_CHILD | BS_CHECKBOX ,210,55,26,10, hWnd,(HMENU)ID6, NULL,NULL);
        c_handel[7] = CreateWindowW(L"Button",L"7",WS_VISIBLE | WS_CHILD | BS_CHECKBOX ,250,55,26,10, hWnd,(HMENU)ID7, NULL,NULL);
        c_handel[8] = CreateWindowW(L"Button",L"8",WS_VISIBLE | WS_CHILD | BS_CHECKBOX ,290,55,26,10, hWnd,(HMENU)ID8, NULL,NULL);
        c_handel[9] = CreateWindowW(L"Button",L"9",WS_VISIBLE | WS_CHILD | BS_CHECKBOX  ,330,55,35,10, hWnd,(HMENU)ID9, NULL,NULL);
        c_handel[10] = CreateWindowW(L"Button",L"10",WS_VISIBLE | WS_CHILD | BS_CHECKBOX ,370,55,35,10, hWnd,(HMENU)ID10, NULL,NULL);
        c_handel[11] = CreateWindowW(L"Button",L"11",WS_VISIBLE | WS_CHILD | BS_CHECKBOX ,410,55,35,10, hWnd,(HMENU)ID11, NULL,NULL);
        c_handel[12] = CreateWindowW(L"Button",L"12",WS_VISIBLE | WS_CHILD | BS_CHECKBOX,450,55,35,10, hWnd,(HMENU)ID12, NULL,NULL);
        c_handel[13] = CreateWindowW(L"Button",L"13",WS_VISIBLE | WS_CHILD | BS_CHECKBOX ,490,55,35,10, hWnd,(HMENU)ID13, NULL,NULL);
        c_handel[14] = CreateWindowW(L"Button",L"14",WS_VISIBLE | WS_CHILD | BS_CHECKBOX ,530,55,35,10, hWnd,(HMENU)ID14, NULL,NULL);
        c_handel[15] = CreateWindowW(L"Button",L"15",WS_VISIBLE | WS_CHILD | BS_CHECKBOX ,570,55,35,10, hWnd,(HMENU)ID15, NULL,NULL);

    }

    void get_textbox(HWND hWnd){}

    void get_finish_button(HWND hWnd){

       CreateWindow("Button","Done",WS_VISIBLE | WS_CHILD ,520,325,60,20,hWnd,(HMENU)button2,NULL,NULL);
       CreateWindow("Static","Remarks : ",WS_VISIBLE | WS_CHILD ,22,325,70,68,hWnd,NULL,NULL,NULL);
       hRe =  CreateWindow("Edit","",WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL | ES_AUTOVSCROLL,95,325,400,20,hWnd,NULL,NULL,NULL);
    }

};

class File_write{

    public:
    char f_t[50],f_class[50],f_name[50],f_sub[50],re[50],buffer[80],final_date[50][50];
    int abs[15]={0},d_count=0,total_abs=0;


           void write(char output[3][50]){


                strcpy(file_name,output[0]);
                strcat(file_name,"_");

                strcat(file_name,output[1]);
                strcat(file_name,"_");

                strcat(file_name,output[2]);
                strcat(file_name,"_");
                File_write obj;
                strcat(file_name,obj.get_date());

                strcat(file_name,".txt");
                strcat(notation,file_name);
                ofstream obj_out(notation);
                obj_out.close();
                cout<<"\n\nFile naming .... done.\n";
                cout<<"Ready for saving info ... done\n\n";
            }

            char* get_date(){

                time_t rawtime;
                struct tm * timeinfo;
                time (&rawtime);
                timeinfo = localtime(&rawtime);
                strftime(buffer,sizeof(buffer),"%d-%m-%Y",timeinfo);
                return buffer;
            }

            char* add_date(){

                 int i,j=0;
                 File_write obj;
                 for(i=0;i<strlen(date[i])+date_count;i++){
                        if(!strcmp(obj.get_date(),date[i]) == 0){
                            strcpy(date[j],obj.get_date());
                            j++;
                        }
                    }
                }

            void read_and_display(HWND hWnd){

            int t=0;
            ifstream dis_obj;
            File_write read_obj;
            dis_obj.open(open_file,std::ios::binary);
            if(dis_obj != NULL){

            dis_obj.read((char *)&read_obj,sizeof(read_obj));
            CreateWindow("Static","Class",WS_VISIBLE | WS_CHILD ,85,135,50,20,hWnd,NULL,NULL,NULL);
            CreateWindow("Static",read_obj.f_class,WS_VISIBLE | WS_CHILD ,85,165,150,20,hWnd,NULL,NULL,NULL);
            CreateWindow("Static","Lecture",WS_VISIBLE | WS_CHILD ,250,135,50,20,hWnd,NULL,NULL,NULL);
            CreateWindow("Static",read_obj.f_sub,WS_VISIBLE | WS_CHILD ,250,165,50,20,hWnd,NULL,NULL,NULL);
            CreateWindow("Static","Absent Roll No.",WS_VISIBLE | WS_CHILD ,450,135,100,20,hWnd,NULL,NULL,NULL);

            for(i=0;i<read_obj.total_abs;i++){

                char buffer[10];
                itoa(read_obj.abs[i],buffer,10);
                CreateWindow("Static",buffer,WS_VISIBLE | WS_CHILD ,450+t,165,100,20,hWnd,NULL,NULL,NULL);
                t = t + 15;
                if(i != read_obj.total_abs-1){
                CreateWindow("Static",",",WS_VISIBLE | WS_CHILD ,450+t,165,100,20,hWnd,NULL,NULL,NULL);

                 t=t+8;
                }
            }

            CreateWindow("Static","Remarks",WS_VISIBLE | WS_CHILD ,660,135,100,20,hWnd,NULL,NULL,NULL);
            CreateWindow("Static",read_obj.re,WS_VISIBLE | WS_CHILD ,660,165,100,20,hWnd,NULL,NULL,NULL);
            dis_obj.close();

            }
            else{
                 cout<<"\nFail to open file";
                 CreateWindow("Static","Record Not Found",WS_VISIBLE | WS_CHILD ,400,250,120,20,hWnd,NULL,NULL,NULL);
            }
        }



            void copy_data(char remark[]){

                 strcpy(f_class,output[0]);
                 strcpy(f_name,output[1]);
                 strcpy(f_sub,output[2]);
                 strcpy(f_t,buffer);
                 strcpy(re,remark);

            }

        void check_and_add(){

                File_write f;
                char date[20],date2[20];
                int length=0;
                fstream fo;
                fo.open("time.txt",ios::out|ios::in);

                    fo.seekg(0,fo.end);
                    length = fo.tellg();
                        if(length == 0){

                                strcpy(date,f.get_date());
                                fo<<date<<"\n";
                                fo.close();
                        }else{
                            fo.close();
                            cout<<"done"<<endl;
                            fstream fo2;
                            fo2.open("time.txt",ios::in|ios::out);
                            fo2.seekg(0,fo2.end);
                            length = fo2.tellg();
                            length = length - 12;
                            fo2.seekg(length,fo2.beg);
                            fo2>>date2;
                            if(!strcmp(date2,f.get_date()) == 0){
                                fo2.seekg(length+12,fo2.beg);
                                fo2<<f.get_date()<<"\n";
                            }
                            fo2.close();
                    }
            }


        void find_abs(){

               int i=0,j=0;
                while(i!=15){

                    if(abs_no[i] != 0){
                        abs[j] = abs_no[i];
                        j++;
                        count_abs++;
                    }
                    i++;
                }

                for(i=0;i<count_abs;i++){
                    printf("%d,",abs[i]);
                }

            }

            void frame_name(){
             for(i=0;i<4;i++){
                if(i==0){
                    strcpy(open_file,temp_name[i]);
                }else{
                    strcat(open_file,temp_name[i]);
                }
             }
                cout<<open_file;
        }

};

class view_att{
HMENU hMenu2,hItem1,hItem2;
public:

    void get_menu(HWND hWnd){
        //for main menu creation
        hMenu2 = CreateMenu();
        //for sub item craation
        hItem1 = CreateMenu();
        //FIle menu tab
        AppendMenu(hMenu2,MF_POPUP,(UINT_PTR)hItem1,"File");

        //File menu item
        AppendMenu(hItem1,MF_STRING,Exit2,"Exit");
        SetMenu(hWnd,hMenu2);
    }

    void get_drop_downs(HWND hWnd){

    CreateWindow("Static","View Mode",WS_VISIBLE | WS_CHILD ,420,15,150,100,hWnd,NULL,NULL,NULL);

        //first label
        int i;
        CreateWindow("Static","Select Class :",WS_VISIBLE | WS_CHILD  ,15,55,150,100,hWnd,NULL,NULL,NULL);
        hDrop4 =  CreateWindow("Combobox","",CBS_DROPDOWNLIST | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE,15, 75, 169, 100, hWnd,(HMENU)drop4, NULL,NULL);
        SendMessage(hDrop4,CB_ADDSTRING,1,(LPARAM)"FY iMCA");
        SendMessage(hDrop4,CB_ADDSTRING,2,(LPARAM)"SY iMCA");
        SendMessage(hDrop4,CB_ADDSTRING,3,(LPARAM)"TY iMCA");
        SendMessage(hDrop4,CB_ADDSTRING,4,(LPARAM)"MCA");

        //second label
        CreateWindow("Static","Select Faculty :",WS_VISIBLE | WS_CHILD ,200,55,150,100,hWnd,NULL,NULL,NULL);
        hDrop5 =  CreateWindow("Combobox","",CBS_DROPDOWNLIST | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE,200, 75, 169, 100, hWnd, (HMENU)drop5, NULL,NULL);
        SendMessage(hDrop5,CB_ADDSTRING,1,(LPARAM)"Siddhi Shah");
        SendMessage(hDrop5,CB_ADDSTRING,2,(LPARAM)"Hiral Vegda");
        SendMessage(hDrop5,CB_ADDSTRING,3,(LPARAM)"Pratik Thanawala");
        SendMessage(hDrop5,CB_ADDSTRING,4,(LPARAM)"Kunjal Gajjar");


        //3rd label
        CreateWindow("Static","Select Lecture :",WS_VISIBLE | WS_CHILD ,385,55,150,100,hWnd,NULL,NULL,NULL);
        hDrop6 =  CreateWindow("Combobox","",CBS_DROPDOWNLIST | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE,385, 75, 169, 100, hWnd, (HMENU)drop6, NULL,NULL);
        SendMessage(hDrop6,CB_ADDSTRING,1,(LPARAM)"SAD");
        SendMessage(hDrop6,CB_ADDSTRING,2,(LPARAM)"DSA");
        SendMessage(hDrop6,CB_ADDSTRING,3,(LPARAM)"MS");
        SendMessage(hDrop6,CB_ADDSTRING,4,(LPARAM)"OOCP");

        CreateWindow("Static","Select Date :",WS_VISIBLE | WS_CHILD ,570,55,150,100,hWnd,NULL,NULL,NULL);
        hDrop7 =  CreateWindow("Combobox","",CBS_DROPDOWNLIST | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE,570, 75, 169, 100, hWnd, (HMENU)drop7, NULL,NULL);
        char d[20];
        File_write q_obj;
        strcpy(d,q_obj.get_date());

       SendMessage(hDrop7,CB_ADDSTRING,4,(LPARAM)d);
       CreateWindow("Button","View",WS_VISIBLE | WS_CHILD ,780,73,60,25,hWnd,(HMENU)button3,NULL,NULL);

    }

     void drop_date(HWND hWnd){

            fstream fo7;
            int len,i=0,cou=0;
            char date[50][50],c,temp[20];
            fo7.open("time.txt",ios::in);
            fo7.seekg(0,ios::beg);
            while(len != -1){
            fo7>>temp;
            strcpy(date[i],temp);
            i++;
            cou++;
            len = fo7.tellg();
            }
            for(i=0;i<cou-2;i++){
                SendMessage(hDrop7,CB_ADDSTRING,i+1,(LPARAM)date[i]);
            }
        }
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance , LPSTR lpCmdLine ,int nCmdShow){

    //first window
    WNDCLASSW wc = {0};
    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wc.hCursor = LoadCursor(NULL,IDC_ARROW);
    wc.hInstance = hInstance;
    wc.lpszClassName = L"MyWindowClass";
    wc.lpfnWndProc = WindowProcedure;

    //Second window
    WNDCLASSW wc1 = {0};
    wc1.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wc1.hCursor = LoadCursor(NULL,IDC_ARROW);
    wc1.hInstance = hInstance;
    wc1.lpszClassName = L"MyWindowClass1";
    wc1.lpfnWndProc = WindowProcedure1;

    WNDCLASSW wc2 = {0};
    wc2.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wc2.hCursor = LoadCursor(NULL,IDC_ARROW);
    wc2.hInstance = hInstance;
    wc2.lpszClassName = L"MyWindowClass2";
    wc2.lpfnWndProc = WindowProcedure2;

    if(!RegisterClassW(&wc)){
        return -1;
    }

    if(!RegisterClassW(&wc1)){
        return -1;
    }

    if(!RegisterClassW(&wc2)){
        return -1;
    }

    //main window
    CreateWindow("MyWindowClass","",WS_OVERLAPPEDWINDOW | WS_VISIBLE ,350,150,220,400,NULL,NULL,NULL,NULL);

    ////First window message loop
    MSG msg = {0};
    while(GetMessage(&msg,NULL,NULL,NULL)){

                TranslateMessage(&msg);
                DispatchMessage(&msg);

          }

    //second window message loop
    MSG msg1 = {0};
    while(GetMessage(&msg1,NULL,NULL,NULL)){

                TranslateMessage(&msg1);
                DispatchMessage(&msg1);

          }
    MSG msg2 = {0};
    while(GetMessage(&msg2,NULL,NULL,NULL)){

                TranslateMessage(&msg2);
                DispatchMessage(&msg2);

          }

return 0;
}
//for first window
LRESULT CALLBACK WindowProcedure(HWND hWnd,UINT msg,WPARAM wp,LPARAM lp)
{
    switch(msg){

    case WM_COMMAND:

        switch(wp){

        case Exit:
             DestroyWindow(hWnd);
                break;
        case view:
             DestroyWindow(hWnd);
             if(open == 0){
                CreateWindow("MyWindowClass2","",WS_OVERLAPPEDWINDOW | WS_VISIBLE ,260,150,900,500,NULL,NULL,NULL,NULL);
                open = 1;
            }

             //DestroyWindow(hWnd);
             break;
        case button:
            if(open == 0){
                CreateWindow("MyWindowClass1","",WS_OVERLAPPEDWINDOW | WS_VISIBLE ,560,150,630,400,NULL,NULL,NULL,NULL);
                open = 1;

            }
            //writing into the file.
            File_write obj;
            obj.write(output);
            File_write k;
            k.check_and_add();

            //obj.write_date();


            cout<<"\nPhase-1 .... done successfully\n";
            break;
        }
        // action for dropdown list
        switch(HIWORD(wp)){

            case CBN_SELCHANGE:

                int wmId;
                wmId = LOWORD(wp);

                if(wmId == drop1){

                    char i[10];
                    char name[4][10] = {"FY iMCA","SY iMCA","TY iMCA","MCA"};
                    int choice,j,q;

                    GetWindowText(hDrop1,i,10);

                    for(j=1;j<=4;j++){
                        q = j-1;
                        if((strcmp(i,name[q])) == 0){
                            strcpy(output[0],name[q]);
                            break;
                        }else{
                            choice = 0;
                        }
                    }

                }else if(wmId == drop2){

                    char i[10];
                    char name[4][20] = {"Siddhi Shah","Hiral Vegda","Pratik Thanawala","Kunjal Gajjar"};
                    int choice,j,q;

                    GetWindowText(hDrop2,i,20);

                    for(j=1;j<=4;j++){
                        q = j-1;
                        if((strcmp(i,name[q])) == 0){
                             strcpy(output[1],name[q]);
                            break;
                        }else{
                            choice = 0;
                        }
                    }

                }else{

                    char i[10];
                    char name[4][10] = {"SAD","DSA" ,"MS","OOCP"};
                    int choice,j,q;

                    GetWindowText(hDrop3,i,10);

                    for(j=1;j<=4;j++){
                        q = j-1;
                        if((strcmp(i,name[q])) == 0){
                            strcpy(output[2],name[q]);
                            break;
                        }else{
                            choice = 0;
                        }
                    }
                }
            break;

        }
        break;

    case WM_CREATE:

        // just like on create function.
        GUI obj;
        obj.get_menu(hWnd);
        obj.get_elements(hWnd);
        break;

    case WM_DESTROY:

        //for closing all active windows.
        PostQuitMessage(0);
        break;

    default:

            //for hendaling other requests.
            DefWindowProc(hWnd,msg,wp,lp);
    }

}
//for second window
LRESULT CALLBACK WindowProcedure1(HWND hWnd1,UINT msg1,WPARAM wp1,LPARAM lp1){


 switch(msg1){

    case WM_COMMAND:

        switch(wp1){

            case button2:

                GetWindowText(hRe,remark,50);
                ofstream file_obj;
                file_obj.open(file_name,std::ios_base::binary);
                if(file_obj != NULL){
                File_write fp,read_obj;
                fp.get_date();
                fp.copy_data(remark);
                fp.find_abs();
                fp.total_abs=count_abs;
                file_obj.write((char *)&fp,sizeof(fp));

                ifstream fp2;
                fp2.open(file_name,std::ios_base::in);
                fp2.read((char *)&read_obj,sizeof(fp));
                printf("\n%s",read_obj.f_t);
                printf("\n%s",read_obj.f_class);
                printf("\n%s",read_obj.f_name);
                printf("\n%s",read_obj.f_sub);
                printf("\n");
                int k=0;
                while(read_obj.abs[k] != 0){
                    printf("%d,",read_obj.abs[k]);
                    k++;
                }
                fp2.close();

                cout<<"\nPhase-2 .... done successfully\n";
                MessageBox(hWnd1,"Attendance Successfully Marked.","Conformation",MB_OK);
                DestroyWindow(hWnd1);
                }else{
                    cout<<"\nWriting into file fail\n";
                }

                cout<<"All set.\n";
                break;
        }

        switch(HIWORD(wp1)){

            //for getting check box state and appending to combo box.
            case BN_CLICKED:
                int wmId;
                wmId = LOWORD(wp1);

               switch(wmId){

                case ID1:

                    if(check[0] == 0){
                    //cout<<"1"<<endl;
                    SendMessage(c_handel[1],BM_SETCHECK,BST_CHECKED, 0);
                    check[0] = 1;
                    abs_no[0] = 1;
                    }else{
                    cout<<"0"<<endl;
                    SendMessage(c_handel[1],BM_SETCHECK,BST_UNCHECKED, 0);
                    SetWindowText(hdisplay,data);
                    check[0] = 0;
                    abs_no[0] = 0;
                    }/*printf("\n");
                    for(i=0;i<15;i++){
                        printf(" %d ",abs_no[i]);
                    }printf("\n");*/
                break;

                case ID2:

                    if(check[1] == 0){
                    cout<<"1"<<endl;
                    SendMessage(c_handel[2],BM_SETCHECK,BST_CHECKED, 0);
                    check[1] = 1;
                    abs_no[1] = 2;
                    }else{
                    cout<<"0"<<endl;
                    SendMessage(c_handel[2],BM_SETCHECK,BST_UNCHECKED, 0);
                    check[1] = 0;
                    abs_no[1]=0;
                    }/*printf("\n");
                    for(i=0;i<15;i++){
                        printf(" %d ",abs_no[i]);
                    }printf("\n");*/
                break;

                case ID3:

                    if(check[2] == 0){
                    cout<<"1"<<endl;
                    SendMessage(c_handel[3],BM_SETCHECK,BST_CHECKED, 0);
                     check[2] = 1;
                     abs_no[2] = 3;
                    }else{
                    cout<<"0"<<endl;
                    SendMessage(c_handel[3],BM_SETCHECK,BST_UNCHECKED, 0);
                    check[2] = 0;
                    abs_no[2]=0;
                }/*printf("\n");
                    for(i=0;i<15;i++){
                        printf(" %d ",abs_no[i]);
                    }printf("\n");*/
                break;

                case ID4:

                    if(check[3] == 0){
                    cout<<"1"<<endl;
                    SendMessage(c_handel[4],BM_SETCHECK,BST_CHECKED, 0);
                    check[3] = 1;
                     abs_no[3] = 4;
                    }else{
                    cout<<"0"<<endl;
                    SendMessage(c_handel[4],BM_SETCHECK,BST_UNCHECKED, 0);
                    check[3] = 0;
                    abs_no[3] = 0;
                }
                break;

                case ID5:

                    if(check[4] == 0){
                    cout<<"1"<<endl;
                    SendMessage(c_handel[5],BM_SETCHECK,BST_CHECKED, 0);
                    check[4] = 1;
                     abs_no[4] = 5;

                    }else{
                    cout<<"0"<<endl;
                    SendMessage(c_handel[5],BM_SETCHECK,BST_UNCHECKED, 0);
                   check[4] = 0;
                   abs_no[4] = 0;
                }
                break;

                case ID6:

                    if(check[5] == 0){
                    cout<<"1"<<endl;
                    SendMessage(c_handel[6],BM_SETCHECK,BST_CHECKED, 0);
                    check[5] = 1;
                     abs_no[5] = 6;

                    }else{
                    cout<<"0"<<endl;
                    SendMessage(c_handel[6],BM_SETCHECK,BST_UNCHECKED, 0);
                    check[5] = 0;
                     abs_no[5] = 0;
                }
                break;

                 case ID7:

                    if(check[6] == 0){
                    cout<<"1"<<endl;
                    SendMessage(c_handel[7],BM_SETCHECK,BST_CHECKED, 0);
                    check[6] = 1;
                     abs_no[6] = 7;

                    }else{
                    cout<<"0"<<endl;
                    SendMessage(c_handel[7],BM_SETCHECK,BST_UNCHECKED, 0);
                    check[6] = 0;
                    abs_no[6] = 0;

                }
                break;

                 case ID8:

                    if(check[7] == 0){
                    cout<<"1"<<endl;
                    SendMessage(c_handel[8],BM_SETCHECK,BST_CHECKED, 0);
                    check[7] = 1;
                     abs_no[7] = 8;
                    }else{
                    cout<<"0"<<endl;
                    SendMessage(c_handel[8],BM_SETCHECK,BST_UNCHECKED, 0);
                    check[7] = 0;
                    abs_no[7] = 0;
                }
                break;

                 case ID9:

                    if(check[8] == 0){
                    cout<<"1"<<endl;
                    SendMessage(c_handel[9],BM_SETCHECK,BST_CHECKED, 0);
                    check[8] = 1;
                     abs_no[8] = 9;

                    }else{
                    cout<<"0"<<endl;
                    SendMessage(c_handel[9],BM_SETCHECK,BST_UNCHECKED, 0);
                    check[8] = 0;
                    abs_no[8] = 0;
                }
                break;

                 case ID10:
                    char temp[10];
                    if(check[9] == 0){
                    cout<<"1"<<endl;
                    SendMessage(c_handel[10],BM_SETCHECK,BST_CHECKED, 0);
                    check[9] = 1;
                     abs_no[9] = 10;

                    }else{
                    cout<<"0"<<endl;
                    SendMessage(c_handel[10],BM_SETCHECK,BST_UNCHECKED, 0);
                    check[9] = 0;
                    abs_no[9] = 0;
                }
                break;

                case ID11:
                    char temp1[10];
                    if(check[10] == 0){
                    cout<<"1"<<endl;
                    SendMessage(c_handel[11],BM_SETCHECK,BST_CHECKED, 0);
                    check[10] = 1;
                     abs_no[10] = 11;

                    }else{
                    cout<<"0"<<endl;
                    SendMessage(c_handel[11],BM_SETCHECK,BST_UNCHECKED, 0);
                    check[10] = 0;
                    abs_no[10] = 0;
                }
                break;

                case ID12:
                    char temp2[10];
                    if(check[11] == 0){
                    cout<<"1"<<endl;
                    SendMessage(c_handel[12],BM_SETCHECK,BST_CHECKED, 0);
                    check[11] = 1;
                     abs_no[11] = 12;

                    }else{
                    cout<<"0"<<endl;
                    SendMessage(c_handel[12],BM_SETCHECK,BST_UNCHECKED, 0);
                    check[11] = 0;
                    abs_no[11] = 0;

                }
                break;

                case ID13:
                    char temp3[10];
                    if(check[12] == 0){
                    cout<<"1"<<endl;
                    SendMessage(c_handel[13],BM_SETCHECK,BST_CHECKED, 0);
                    check[12] = 1;
                     abs_no[12] = 13;

                    }else{
                    cout<<"0"<<endl;
                    SendMessage(c_handel[13],BM_SETCHECK,BST_UNCHECKED, 0);
                    check[12] = 0;
                    abs_no[12] = 0;

                }
                break;

                case ID14:

                    char temp4[10];
                    if(check[13] == 0){
                    cout<<"1"<<endl;
                    SendMessage(c_handel[14],BM_SETCHECK,BST_CHECKED, 0);
                    check[13] = 1;
                     abs_no[13] = 14;

                    }else{
                    cout<<"0"<<endl;
                    SendMessage(c_handel[14],BM_SETCHECK,BST_UNCHECKED, 0);
                    check[13] = 0;
                    abs_no[13] = 0;

                }
                break;

                case ID15:

                    char temp5[15];
                    if(check[14] == 0){
                    cout<<"1"<<endl;
                    SendMessage(c_handel[15],BM_SETCHECK,BST_CHECKED, 0);
                    check[14] = 1;
                     abs_no[14] = 15;

                    }else{
                    cout<<"0"<<endl;
                    SendMessage(c_handel[15],BM_SETCHECK,BST_UNCHECKED, 0);
                    check[14] = 0;
                    abs_no[14] = 0;

                }

                break;
                }
                }

        break;

    case WM_CREATE:

        // on create function
        GUI obj1;
        obj1.get_check_box(hWnd1);
        obj1.get_textbox(hWnd1);
        obj1.get_finish_button(hWnd1);

        break;

    case WM_DESTROY:

        PostQuitMessage(0);
        open = 0;
        break;

    default:
            DefWindowProc(hWnd1,msg1,wp1,lp1);
    }

}

LRESULT CALLBACK WindowProcedure2(HWND hWnd2,UINT msg2,WPARAM wp2,LPARAM lp2){

 switch(msg2){

    case WM_COMMAND:

    switch(wp2){

        case Exit2:
        DestroyWindow(hWnd2);
        break;

        case button3:
            File_write o;
            o.frame_name();
            o.read_and_display(hWnd2);
            break;

        }
    switch(HIWORD(wp2)){

        case CBN_SELCHANGE:

             int wmId1;
             char temp[20];
             wmId1 = LOWORD(wp2);

             if(wmId1 == drop4){
                GetWindowText(hDrop4,temp,20);
                strcpy(temp_name[0],temp);
                strcat(temp_name[0],"_");
               // cout<<"\n"<<open_file;

             }else if(wmId1 == drop5){
                GetWindowText(hDrop5,temp,20);
                strcpy(temp_name[1],temp);
                strcat(temp_name[1],"_");
               // cout<<"\n"<<open_file;

             }else if(wmId1 == drop6){
                GetWindowText(hDrop6,temp,20);
                strcpy(temp_name[2],temp);
                strcat(temp_name[2],"_");
                //cout<<"\n"<<open_file;

             }else if(wmId1 == drop7){
                GetWindowText(hDrop7,temp,20);
                strcpy(temp_name[3],temp);
                strcat(temp_name[3],".txt");
                //cout<<"\n"<<open_file;
             }
            break;

    }
        break;


    case WM_DESTROY:

        PostQuitMessage(0);
        open = 0;
        break;
    case WM_CREATE:
        // just like on create function
        view_att obj;
        obj.get_menu(hWnd2);
        obj.get_drop_downs(hWnd2);
        obj.drop_date(hWnd2);
        break;

    default:
        DefWindowProc(hWnd2,msg2,wp2,lp2);
 }
}

