#include<windows.h>
#include<iostream>
#include<cstring>
#include<fstream>
#include<ctime>

#define Exit 10
#define button 6
#define button2 9
#define win1 7
#define win2 8
#define ID1 1
#define ID2 2
#define ID3 3
#define ID4 4
#define ID5 5
#define ID6 13
#define ID7 14
#define ID8 15
#define ID9 16
#define ID10 17
#define ID11 18
#define ID12 19
#define ID13 20
#define ID14 21
#define ID15 22
#define drop1 10
#define drop2 11
#define drop3 12

using namespace std;
LRESULT CALLBACK WindowProcedure(HWND,UINT,WPARAM,LPARAM);
LRESULT CALLBACK WindowProcedure1(HWND hWnd,UINT msg,WPARAM wp,LPARAM lp);

//global variable.

int open = 0,i,check[15]={0},p1=0,p2=0,c[15],q[15]={0};
char output[3][50],file_name[100],remark[50];
char data[400];
char dis[400];
char notation[20] = "..//Attendance_log/";

HWND c_handel[32],hdisplay;
HWND hDrop1,hDrop2,hDrop3,hCheckBox1,hCheckBox2,hRe;

// GUI class
class GUI{
HMENU hMenu;
HMENU hMenu1Item,hMenu2Item;
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
        //help tab
        AppendMenu(hMenu,MF_POPUP,(UINT_PTR)hMenu2Item,"Help");
        SetMenu(hWnd,hMenu);
    }

    void get_elements(HWND hWnd){

        CreateWindowW(L"Static",L"Select Lecture Details",WS_VISIBLE | WS_CHILD ,35,15,150,100,hWnd,NULL,NULL,NULL);

        //first label
        CreateWindowW(L"Static",L"Select Class :",WS_VISIBLE | WS_CHILD ,15,55,150,100,hWnd,NULL,NULL,NULL);
        hDrop1 =  CreateWindowW(L"Combobox",L"",CBS_DROPDOWNLIST | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE,15, 75, 169, 100, hWnd,(HMENU)drop1, NULL,NULL);
        SendMessage(hDrop1,CB_ADDSTRING,1,(LPARAM)"FY iMCA");
        SendMessage(hDrop1,CB_ADDSTRING,2,(LPARAM)"SY iMCA");
        SendMessage(hDrop1,CB_ADDSTRING,3,(LPARAM)"TY iMCA");
        SendMessage(hDrop1,CB_ADDSTRING,4,(LPARAM)"MCA");

        //second label
        CreateWindowW(L"Static",L"Select Faculty :",WS_VISIBLE | WS_CHILD ,15,120,150,100,hWnd,NULL,NULL,NULL);
        hDrop2 =  CreateWindowW(L"Combobox",L"",CBS_DROPDOWNLIST | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE,15, 145, 169, 100, hWnd, (HMENU)drop2, NULL,NULL);
        SendMessage(hDrop2,CB_ADDSTRING,1,(LPARAM)"Siddhi Shah");
        SendMessage(hDrop2,CB_ADDSTRING,2,(LPARAM)"Hiral Vegda");
        SendMessage(hDrop2,CB_ADDSTRING,3,(LPARAM)"Pratik Thanawala");
        SendMessage(hDrop2,CB_ADDSTRING,4,(LPARAM)"Kunjal Gajjar");


        //3rd label
        CreateWindowW(L"Static",L"Select Lecture :",WS_VISIBLE | WS_CHILD ,15,190,150,100,hWnd,NULL,NULL,NULL);
        hDrop3 =  CreateWindowW(L"Combobox",L"",CBS_DROPDOWNLIST | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE,15, 215, 169, 100, hWnd, (HMENU)drop3, NULL,NULL);
        SendMessage(hDrop3,CB_ADDSTRING,1,(LPARAM)"SAD");
        SendMessage(hDrop3,CB_ADDSTRING,2,(LPARAM)"DSA");
        SendMessage(hDrop3,CB_ADDSTRING,3,(LPARAM)"MS");
        SendMessage(hDrop3,CB_ADDSTRING,4,(LPARAM)"OOCP");


        //button
        CreateWindowW(L"Button",L"Mark",WS_VISIBLE | WS_CHILD ,75,265,60,25,hWnd,(HMENU)button,NULL,NULL);
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

    void get_textbox(HWND hWnd){

    hdisplay = CreateWindowW(L"Edit",L"",WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL | ES_AUTOVSCROLL,20,110,570,200,hWnd,NULL,NULL,NULL);

    }

    void get_finish_button(HWND hWnd){
       CreateWindowW(L"Button",L"Done",WS_VISIBLE | WS_CHILD ,520,325,60,20,hWnd,(HMENU)button2,NULL,NULL);
       CreateWindowW(L"Static",L"Remarks : ",WS_VISIBLE | WS_CHILD ,22,325,70,68,hWnd,NULL,NULL,NULL);
       hRe =  CreateWindowW(L"Edit",L"",WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL | ES_AUTOVSCROLL,95,325,400,20,hWnd,NULL,NULL,NULL);
    }

};

class File_write{
    public:

            void write(char output[3][50]){

                //for date
                time_t rawtime;
                struct tm * timeinfo;
                char buffer[80];
                time (&rawtime);
                timeinfo = localtime(&rawtime);
                strftime(buffer,sizeof(buffer),"%d-%m-%Y",timeinfo);


                strcpy(file_name,output[0]);
                strcat(file_name,"_");
                strcat(file_name,output[1]);
                strcat(file_name,"_");
                strcat(file_name,output[2]);
                strcat(file_name,"_");
                strcat(file_name,buffer);
                strcat(file_name,".txt");
                strcat(notation,file_name);
                ofstream obj_out(notation);
                obj_out.close();
                cout<<"\n\nFile naming .... done.\n";
                cout<<"Ready for saving info ... done\n\n";

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

    if(!RegisterClassW(&wc)){
        return -1;
    }

    if(!RegisterClassW(&wc1)){
        return -1;
    }

    //main window
    CreateWindowW(L"MyWindowClass",L"",WS_OVERLAPPEDWINDOW | WS_VISIBLE ,350,150,220,400,NULL,NULL,NULL,NULL);

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
        case button:
            if(open == 0){
                CreateWindowW(L"MyWindowClass1",L"",WS_OVERLAPPEDWINDOW | WS_VISIBLE ,560,150,630,400,NULL,NULL,NULL,NULL);
                open = 1;

            }
            //writing into the file.
            File_write obj;
            obj.write(output);
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
                file_obj.open(notation,std::ios_base::out);
                if(file_obj != NULL){
                file_obj<<"\n------------------------------------------------------------------------------------------\n";
                file_obj<<"Remarks : "<<remark;
                file_obj<<"\n------------------------------------------------------------------------------------------\n";
                file_obj<<"Absent Roll No :  "<<data;
                file_obj.close();
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
                    //for appending
                    data[p1] = '1';
                    c[0] = p1;
                    p1++;
                    data[p1] = ',';
                    q[0] = p1;
                    p1++;

                    SetWindowText(hdisplay,data);

                    }else{
                    cout<<"0"<<endl;
                    SendMessage(c_handel[1],BM_SETCHECK,BST_UNCHECKED, 0);
                    check[0] = 0;
                    data[c[0]] = ' ';
                    data[q[0]] = ' ';
                    SetWindowText(hdisplay,data);
                    }
                break;

                case ID2:

                    if(check[1] == 0){
                    cout<<"1"<<endl;
                    SendMessage(c_handel[2],BM_SETCHECK,BST_CHECKED, 0);
                    check[1] = 1;
                    data[p1] = '2';
                    c[1] = p1;
                    p1++;
                    data[p1] = ',';
                    q[1] = p1;
                    p1++;
                    SetWindowText(hdisplay,data);
                    }else{
                    cout<<"0"<<endl;
                    SendMessage(c_handel[2],BM_SETCHECK,BST_UNCHECKED, 0);
                    check[1] = 0;
                    data[c[1]] = ' ';
                    data[q[1]] = ' ';
                    SetWindowText(hdisplay,data);
                    }
                break;

                case ID3:

                    if(check[2] == 0){
                    cout<<"1"<<endl;
                    SendMessage(c_handel[3],BM_SETCHECK,BST_CHECKED, 0);
                    check[2] = 1;
                    data[p1] = '3';
                    c[2] = p1;
                    p1++;
                    data[p1] = ',';
                    q[2] = p1;
                    p1++;
                    SetWindowText(hdisplay,data);
                    }else{
                    cout<<"0"<<endl;
                    SendMessage(c_handel[3],BM_SETCHECK,BST_UNCHECKED, 0);
                    data[c[2]] = ' ';
                    data[q[2]] = ' ';
                    SetWindowText(hdisplay,data);
                    check[2] = 0;
                }
                break;

                case ID4:

                    if(check[3] == 0){
                    cout<<"1"<<endl;
                    SendMessage(c_handel[4],BM_SETCHECK,BST_CHECKED, 0);
                    check[3] = 1;
                    data[p1] = '4';
                    c[3] = p1;
                    p1++;
                    data[p1] = ',';
                    q[3] = p1;
                    p1++;
                    SetWindowText(hdisplay,data);
                    }else{
                    cout<<"0"<<endl;
                    SendMessage(c_handel[4],BM_SETCHECK,BST_UNCHECKED, 0);
                    check[3] = 0;
                    data[c[3]] = ' ';
                    data[q[3]] = ' ';
                    SetWindowText(hdisplay,data);

                }
                break;

                case ID5:

                    if(check[4] == 0){
                    cout<<"1"<<endl;
                    SendMessage(c_handel[5],BM_SETCHECK,BST_CHECKED, 0);
                    check[4] = 1;
                    data[p1] = '5';
                    c[4] = p1;
                    p1++;
                    data[p1] = ',';
                    q[4] = p1;
                    p1++;
                    SetWindowText(hdisplay,data);
                    }else{
                    cout<<"0"<<endl;
                    SendMessage(c_handel[5],BM_SETCHECK,BST_UNCHECKED, 0);
                    check[4] = 0;
                    data[c[4]] = ' ';
                    data[q[4]] = ' ';
                    SetWindowText(hdisplay,data);

                }
                break;

                case ID6:

                    if(check[5] == 0){
                    cout<<"1"<<endl;
                    SendMessage(c_handel[6],BM_SETCHECK,BST_CHECKED, 0);
                    check[5] = 1;
                    data[p1] = '6';
                    c[5] = p1;
                    p1++;
                    data[p1] = ',';
                    q[5] = p1;
                    p1++;
                    SetWindowText(hdisplay,data);
                    }else{
                    cout<<"0"<<endl;
                    SendMessage(c_handel[6],BM_SETCHECK,BST_UNCHECKED, 0);
                    check[5] = 0;
                }
                break;

                 case ID7:

                    if(check[6] == 0){
                    cout<<"1"<<endl;
                    SendMessage(c_handel[7],BM_SETCHECK,BST_CHECKED, 0);
                    check[6] = 1;
                    data[p1] = '7';
                    c[6] = p1;
                    p1++;
                    data[p1] = ',';
                    q[6] = p1;
                    p1++;
                    SetWindowText(hdisplay,data);
                    }else{
                    cout<<"0"<<endl;
                    SendMessage(c_handel[7],BM_SETCHECK,BST_UNCHECKED, 0);
                    check[6] = 0;
                }
                break;

                 case ID8:

                    if(check[7] == 0){
                    cout<<"1"<<endl;
                    SendMessage(c_handel[8],BM_SETCHECK,BST_CHECKED, 0);
                    check[7] = 1;
                    data[p1] = '8';
                    c[7] = p1;
                    p1++;
                    data[p1] = ',';
                    q[7] = p1;
                    p1++;
                    SetWindowText(hdisplay,data);
                    }else{
                    cout<<"0"<<endl;
                    SendMessage(c_handel[8],BM_SETCHECK,BST_UNCHECKED, 0);
                    check[7] = 0;
                }
                break;

                 case ID9:

                    if(check[8] == 0){
                    cout<<"1"<<endl;
                    SendMessage(c_handel[9],BM_SETCHECK,BST_CHECKED, 0);
                    check[8] = 1;
                    data[p1] = '9';
                    c[8] = p1;
                    p1++;
                    data[p1] = ',';
                    q[8] = p1;
                    p1++;
                    SetWindowText(hdisplay,data);
                    }else{
                    cout<<"0"<<endl;
                    SendMessage(c_handel[9],BM_SETCHECK,BST_UNCHECKED, 0);
                    check[8] = 0;
                }
                break;

                 case ID10:
                    char temp[10];
                    if(check[9] == 0){
                    cout<<"1"<<endl;
                    SendMessage(c_handel[10],BM_SETCHECK,BST_CHECKED, 0);
                    check[9] = 1;
                    GetWindowText(c_handel[10],temp,10);

                    c[9] = p1;
                    for(i=0;i<2;i++){
                            data[p1]=temp[i];
                            p1++;

                    }
                    data[p1] = ',';
                    q[9] = p1;
                    p1++;
                    SetWindowText(hdisplay,data);
                    }else{
                    cout<<"0"<<endl;
                    SendMessage(c_handel[10],BM_SETCHECK,BST_UNCHECKED, 0);
                    for(i=0;i<2;i++){
                    data[c[9]+i] = ' ';
                    }
                    data[q[9]] = ' ';
                    SetWindowText(hdisplay,data);
                    check[9] = 0;
                }
                break;

                case ID11:
                    char temp1[10];
                    if(check[10] == 0){
                    cout<<"1"<<endl;
                    SendMessage(c_handel[11],BM_SETCHECK,BST_CHECKED, 0);
                    check[10] = 1;
                    c[10] = p1;
                    GetWindowText(c_handel[11],temp1,10);
                    for(i=0;i<2;i++){
                            data[p1]=temp1[i];
                            p1++;

                    }
                    data[p1] = ',';
                    q[10] = p1;
                    p1++;
                    SetWindowText(hdisplay,data);
                    }else{
                    cout<<"0"<<endl;
                    SendMessage(c_handel[11],BM_SETCHECK,BST_UNCHECKED, 0);
                    check[10] = 0;
                    for(i=0;i<2;i++){
                    data[c[10]+i] = ' ';
                    }
                    data[q[10]] = ' ';
                    SetWindowText(hdisplay,data);
                }
                break;

                case ID12:
                    char temp2[10];
                    if(check[11] == 0){
                    cout<<"1"<<endl;
                    SendMessage(c_handel[12],BM_SETCHECK,BST_CHECKED, 0);
                    check[11] = 1;
                    c[11] = p1;
                    GetWindowText(c_handel[12],temp2,10);
                    for(i=0;i<2;i++){
                            data[p1]=temp2[i];
                            p1++;

                    }
                    data[p1] = ',';
                    q[11] = p1;
                    p1++;
                    SetWindowText(hdisplay,data);
                    }else{
                    cout<<"0"<<endl;
                    SendMessage(c_handel[12],BM_SETCHECK,BST_UNCHECKED, 0);
                    check[11] = 0;
                    for(i=0;i<2;i++){
                    data[c[11]+i] = ' ';
                    }
                    data[q[11]] = ' ';
                    SetWindowText(hdisplay,data);
                }
                break;

                case ID13:
                    char temp3[10];
                    if(check[12] == 0){
                    cout<<"1"<<endl;
                    SendMessage(c_handel[13],BM_SETCHECK,BST_CHECKED, 0);
                    check[12] = 1;
                    c[12] = p1;
                    GetWindowText(c_handel[13],temp3,10);
                    for(i=0;i<2;i++){
                            data[p1]=temp3[i];
                            p1++;

                    }
                    data[p1] = ',';
                    q[12] = p1;
                    p1++;
                    SetWindowText(hdisplay,data);
                    }else{
                    cout<<"0"<<endl;
                    SendMessage(c_handel[13],BM_SETCHECK,BST_UNCHECKED, 0);
                    check[12] = 0;
                    for(i=0;i<2;i++){
                    data[c[12]+i] = ' ';
                    }
                    data[q[12]] = ' ';
                    SetWindowText(hdisplay,data);
                }
                break;

                case ID14:

                    char temp4[10];
                    if(check[13] == 0){
                    cout<<"1"<<endl;
                    SendMessage(c_handel[14],BM_SETCHECK,BST_CHECKED, 0);
                    check[13] = 1;
                    c[13] = p1;
                    GetWindowText(c_handel[14],temp4,10);
                    for(i=0;i<2;i++){
                            data[p1]=temp4[i];
                            p1++;

                    }
                    data[p1] = ',';
                    q[13] = p1;
                    p1++;
                    SetWindowText(hdisplay,data);
                    }else{
                    cout<<"0"<<endl;
                    SendMessage(c_handel[14],BM_SETCHECK,BST_UNCHECKED, 0);
                    check[13] = 0;
                    for(i=0;i<2;i++){
                    data[c[13]+i] = ' ';
                    }
                    data[q[13]] = ' ';
                    SetWindowText(hdisplay,data);
                }
                break;

                case ID15:

                    char temp5[15];
                    if(check[14] == 0){
                    cout<<"1"<<endl;
                    SendMessage(c_handel[15],BM_SETCHECK,BST_CHECKED, 0);
                    check[14] = 1;
                    c[14] = p1;
                    GetWindowText(c_handel[15],temp5,10);
                    for(i=0;i<2;i++){
                            data[p1]=temp5[i];
                            p1++;

                    }
                    data[p1] = ',';
                    q[14] = p1;
                    p1++;
                    SetWindowText(hdisplay,data);
                    }else{
                    cout<<"0"<<endl;
                    SendMessage(c_handel[15],BM_SETCHECK,BST_UNCHECKED, 0);
                    check[14] = 0;
                    for(i=0;i<2;i++){
                    data[c[14]+i] = ' ';
                    }
                    data[q[14]] = ' ';
                    SetWindowText(hdisplay,data);
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

