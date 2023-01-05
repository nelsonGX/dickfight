/* INCLUDE */
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <sys/select.h>


int delay(int milliseconds)
{
    long pause;
    clock_t now,then;
    now = then = clock();
    pause = milliseconds*(CLOCKS_PER_SEC/1000);
    while( (now-then) < pause ){
        now = clock();
    }
    return 1;
}

int cls()
{
    printf("\033[H\033[J");
}

/* When game opened */
int logo()
{
    printf("  _____  _      _          \n");
    printf(" |  __ \\(_)    | |         \n");
    printf(" | |  | |_  ___| | __      \n");
    printf(" | |  | | |/ __| |/ /      \n");
    printf(" | |__| | | (__|   <       \n");
    printf(" |_____/|_|\\___|_|\\_\\      \n");
    printf("               _______ _       _     _   \n");
    printf("               |  ____(_)     | |   | |  \n");
    printf("               | |__   _  __ _| |__ | |_ \n");
    printf("               |  __| | |/ _` | '_ \\| __|\n");
    printf("               | |    | | (_| | | | | |_ \n");
    printf("               |_|    |_|\\__, |_| |_|\\__|\n");
    printf("                          __/ |             v1.0 [LINUX x86]\n");
    printf("                         |___/              by Nelson (https://dickfight.nelsongx.com)\n");
    printf("\n\n");
}

int c3()
{
    printf("\n\n          ██████╗          \n");    printf("          ╚════██╗         \n");    printf("           █████╔╝         \n");    printf("           ╚═══██╗         \n");    printf("          ██████╔╝██╗██╗██╗\n");    printf("          ╚═════╝ ╚═╝╚═╝╚═╝\n");}
int c2()
{
    printf("\n\n          ██████╗\n");    printf("          ╚════██╗\n");    printf("           █████╔╝\n");    printf("          ██╔═══╝\n");    printf("          ███████╗██╗██╗██╗\n");    printf("          ╚══════╝╚═╝╚═╝╚═╝\n");}
int c1()
{
    printf("\n\n           ██╗\n");     printf("          ███║\n");    printf("          ╚██║\n");    printf("           ██║\n");    printf("           ██║██╗██╗██╗\n");    printf("           ╚═╝╚═╝╚═╝╚═╝\n");}
int cgo()
{
    printf("\n\n           ██████╗  ██████╗ ██╗\n");    printf("          ██╔════╝ ██╔═══██╗██║\n");    printf("          ██║  ███╗██║   ██║██║\n");    printf("          ██║   ██║██║   ██║╚═╝\n");    printf("          ╚██████╔╝╚██████╔╝██╗\n");    printf("           ╚═════╝  ╚═════╝ ╚═╝\n");}

int start()
{
    fd_set read_fds;
    struct timeval timeout;
    int ret;
    char c;
    for(int i=1; i>0; i++){
        FD_ZERO(&read_fds);
        FD_SET(0, &read_fds);
        timeout.tv_sec = 0;
        timeout.tv_usec = 0;
        ret = select(1, &read_fds, NULL, NULL, &timeout);
        if (ret == -1) {
            perror("select");
            return 1;
        } else if (ret > 0) {
            if (FD_ISSET(0, &read_fds)) {
                c = getchar();
                break;
            }
        }
        logo();
        if(i%2==0){
            printf("       > ");
            printf("press [ENTER] to start");
            printf(" <");
            printf("\n");
        }
        else{
            printf("       > ");
            printf("                      ");
            printf(" <");
            printf("\n");
        }
        delay(500);
        cls();
    }
    cls();
    logo();
    printf("       > ");
    printf("press [A] for English, 按下[B]以使用中文");
    printf(" <");
    printf("\n");
    c=getchar();
    if(c=='a'){
        return 1;
    }
    else if(c=='b'){
        return 2;
    }
    else{}
    
}

//loading
int loading()
{
    cls();
    logo();
    printf("  LOADING... [||             ]\n");
    delay(100);
    cls();
    logo();
    printf("  LOADING... [|||||          ]\n");
    delay(100);
    cls();
    logo();
    printf("  LOADING... [||||||||||     ]\n");
    delay(100);
    cls();
    logo();
    printf("  LOADING... [||||||||||||   ]\n");
    delay(100);
    cls();
    logo();
    printf("  LOADING... [|||||||||||||||]\n");
    delay(100);

}
int loadingz()
{
    cls();
    logo();
    printf("  載入中... [||             ]\n");
    delay(100);
    cls();
    logo();
    printf("  載入中... [|||||          ]\n");
    delay(100);
    cls();
    logo();
    printf("  載入中... [||||||||||     ]\n");
    delay(100);
    cls();
    logo();
    printf("  載入中... [||||||||||||   ]\n");
    delay(100);
    cls();
    logo();
    printf("  載入中... [|||||||||||||||]\n");
    delay(100);

}

/* Keyboard movemets */
int key()
{
    int c;
    static struct termios oldt, newt;
    tcgetattr( STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON);
    tcsetattr( STDIN_FILENO, TCSANOW, &newt);
    while((c=getchar())!= 'z'){   
        if(c=='q'){
            return 1;
        }
        else if(c=='\n'){
            return 3;
        }
        else if(c=='w'){
            return 4;
        }
        else if(c=='a' || c==37){
            return 5;
        }
        else if(c=='s'){
            return 6;
        }
        else if(c=='d' || c==39){
            return 7;
        }
        break;
    }
    tcsetattr( STDIN_FILENO, TCSANOW, &oldt);
}

int ready(){
    cls();c3();delay(1000);cls();c2();delay(1000);cls();c1();delay(1000);cls();cgo();delay(500);
}



/* #GAME */
int wasd(int n)
{
    cls();
    if(n==0){
        printf("\n");
        printf("        ██     ██       \n");
        printf("        ██     ██       \n");
        printf("        ██  █  ██       \n");
        printf("        ██ ███ ██       \n");
        printf("         ███ ███        \n");
        printf("                         \n");
        printf("  █████  ███████ ██████  \n");
        printf(" ██   ██ ██      ██   ██ \n");
        printf(" ███████ ███████ ██   ██ \n");
        printf(" ██   ██      ██ ██   ██ \n");
        printf(" ██   ██ ███████ ██████  \n");
    }
    else if(n==4){
        printf("     █████████████\n");
        printf("     ██  █████  ██       \n");
        printf("     ██  █████  ██     \n");
        printf("     ██  ██ ██  ██       \n");
        printf("     ██  █   █  ██     \n");
        printf("     ███   █   ███     \n");
        printf("     █████████████       \n");
        printf("  █████  ███████ ██████  \n");
        printf(" ██   ██ ██      ██   ██ \n");
        printf(" ███████ ███████ ██   ██ \n");
        printf(" ██   ██      ██ ██   ██ \n");
        printf(" ██   ██ ███████ ██████  \n");
    }
    else if(n==5){
        printf("\n");
        printf("        ██     ██       \n");
        printf("        ██     ██       \n");
        printf("        ██  █  ██       \n");
        printf("        ██ ███ ██       \n");
        printf("         ███ ███        \n");
        printf("█████████               \n");
        printf("██     █████████ ██████  \n");
        printf("█  ███  ███      ██   ██ \n");
        printf("█       ████████ ██   ██ \n");
        printf("█  ███  █     ██ ██   ██ \n");
        printf("█  ███  ████████ ██████  \n");
        printf("█████████\n");
    }
    else if(n==6){
        printf("\n");
        printf("        ██     ██       \n");
        printf("        ██     ██       \n");
        printf("        ██  █  ██       \n");
        printf("        ██ ███ ██       \n");
        printf("         ███ ███        \n");
        printf("        █████████          \n");
        printf("  █████ █       ███████  \n");
        printf(" ██   ███  ████████   ██ \n");
        printf(" ████████       ███   ██ \n");
        printf(" ██   ████████  ███   ██ \n");
        printf(" ██   ███       ███████  \n");
        printf("        █████████\n");
    }
    else if(n==7){
        printf("\n");
        printf("        ██     ██       \n");
        printf("        ██     ██       \n");
        printf("        ██  █  ██       \n");
        printf("        ██ ███ ██       \n");
        printf("         ███ ███      \n");
        printf("                 ██████████\n");
        printf("  █████  ██████████      ██\n");
        printf(" ██   ██ ██     ███   ██  █\n");
        printf(" ███████ ██████████   ██  █\n");
        printf(" ██   ██      █████   ██  █\n");
        printf(" ██   ██ ██████████       █\n");
        printf("                 ██████████\n");
        printf("                        \n");
    }
    else if(n==3){
        return 69;
    }
    printf("\n\npress [ENTER] to return");
}

//tutorial
int tutorial()
{
    int a;
    cls();
    logo();
    printf("Welcome to Dick Fight!\nHere's some basic tutorials.\n\n\n");
    printf("                >> press [ENTER] to continue\n                         [Q]     to skip tutorial\n");
    int r=key();
    if(r==3){
        cls();
        logo();
        printf("In this game, there will be dick missles attacking you. If a dick missle touches your dick, you dies.\nYou need to use [A] and [D] to move your dick, You can use [W] to shoot them and get scores.\n Press [W] now so you can test if the keyboard is working.\n\n");
        printf("                >> press [ENTER] to continue\n");
        printf("                >> press [W]     to enter the keyboard testing area\n");
        if(key()==4){
            while(1)
            {
                wasd(0);
                a=key();
                if(wasd(a)==69){break;}
                delay(200);
                wasd(0);
            }
        }
        cls();
        logo();
        printf("The game will speed up after a while.\n\n\n");
        printf("                >> press [ENTER] to continue\n");
        getchar();
        cls();
        logo();
        printf("ARE YOU READY?\n\n\n");
        printf("                >> press [ENTER] to start the game\n");
        getchar();
        ready();
    }
    else if(r==1){
        //ready();
    }
}
int tutorialz()
{
    int a;
    cls();
    logo();
    printf("歡迎來到 Dick Fight!\n這裡是遊戲教學。\n\n\n");
    printf("                >> 按下 [ENTER] 鍵以繼續\n                         [Q]     鍵以跳過教學\n");
    int r=key();
    if(r==3){
        cls();
        logo();
        printf("在這遊戲中，將會有許多Dick導彈攻擊您。 如果有Dick導彈碰到了您的Dick，您將會陽痿(死亡)。\n您必須使用 [A] 和 [D] 鍵來移動您的Dick。您可以使用 [W] 鍵來射擊Dick導彈以得到分數。\n 您可以現在按下 [W] 按鍵測試鍵盤是否有用。\n\n");
        printf("                >> 按下 [ENTER] 鍵以繼續\n");
        printf("                >> 按下 [W]     鍵進入鍵盤測試區域\n");
        if(key()==4){
            while(1)
            {
                wasd(0);
                a=key();
                if(wasd(a)==69){break;}
                delay(200);
                wasd(0);
            }
        }
        cls();
        logo();
        printf("遊戲在一段時間後會加速(Dick導彈會變快)。\n\n\n");
        printf("                >> 按下 [ENTER] 鍵以繼續\n");
        getchar();
        cls();
        logo();
        printf("您準備好了嗎??\n\n\n");
        printf("                >> 按下 [ENTER] 鍵以進入遊戲\n");
        getchar();
        ready();
    }
    else if(r==1){
        //ready();
    }
}

// top display
int display(int health, int score, int tick, int tps)
{
    printf("SCORE %d  |  TICK %d (TPS:%d) | press [ENTER] to exit\n",score, tick, tps);
    return 0;
}
int displayz(int health, int score, int tick, int tps)
{
    printf("分數: %d  |  時間刻: %d (TPS:%d) | 按下 [ENTER] 來結束遊戲\n",score, tick, tps);
    return 0;
}

int space(int spaces)
{
    for(int i=0;i<spaces;i++){
        printf(" ");
    }
}

int render_dick(int mv)
{
    mv=mv*4;
    space(mv); printf("    ###    \n");
    space(mv); printf("    ###    \n");
    space(mv); printf("    ###    \n");
    space(mv); printf("    ###    \n");
    space(mv); printf("###    ###\n");
    space(mv); printf("###    ###\n");
}


int render_screen(int s[100][150])
{
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",s[0][0],s[1][0],s[2][0],s[3][0],s[4][0],s[5][0],s[6][0],s[7][0],s[8][0],s[9][0],s[10][0],s[11][0],s[12][0],s[13][0],s[14][0],s[15][0],s[16][0],s[17][0],s[18][0],s[19][0],s[20][0],s[21][0],s[22][0],s[23][0],s[24][0],s[25][0],s[26][0],s[27][0],s[28][0],s[29][0],s[30][0],s[31][0],s[32][0],s[33][0],s[34][0],s[35][0],s[36][0],s[37][0],s[38][0],s[39][0],s[40][0],s[41][0],s[42][0],s[43][0],s[44][0],s[45][0],s[46][0],s[47][0],s[48][0],s[49][0],s[50][0],s[51][0],s[52][0],s[53][0],s[54][0],s[55][0],s[56][0],s[57][0],s[58][0],s[59][0]);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",s[0][1],s[1][1],s[2][1],s[3][1],s[4][1],s[5][1],s[6][1],s[7][1],s[8][1],s[9][1],s[10][1],s[11][1],s[12][1],s[13][1],s[14][1],s[15][1],s[16][1],s[17][1],s[18][1],s[19][1],s[20][1],s[21][1],s[22][1],s[23][1],s[24][1],s[25][1],s[26][1],s[27][1],s[28][1],s[29][1],s[30][1],s[31][1],s[32][1],s[33][1],s[34][1],s[35][1],s[36][1],s[37][1],s[38][1],s[39][1],s[40][1],s[41][1],s[42][1],s[43][1],s[44][1],s[45][1],s[46][1],s[47][1],s[48][1],s[49][1],s[50][1],s[51][1],s[52][1],s[53][1],s[54][1],s[55][1],s[56][1],s[57][1],s[58][1],s[59][1]);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",s[0][2],s[1][2],s[2][2],s[3][2],s[4][2],s[5][2],s[6][2],s[7][2],s[8][2],s[9][2],s[10][2],s[11][2],s[12][2],s[13][2],s[14][2],s[15][2],s[16][2],s[17][2],s[18][2],s[19][2],s[20][2],s[21][2],s[22][2],s[23][2],s[24][2],s[25][2],s[26][2],s[27][2],s[28][2],s[29][2],s[30][2],s[31][2],s[32][2],s[33][2],s[34][2],s[35][2],s[36][2],s[37][2],s[38][2],s[39][2],s[40][2],s[41][2],s[42][2],s[43][2],s[44][2],s[45][2],s[46][2],s[47][2],s[48][2],s[49][2],s[50][2],s[51][2],s[52][2],s[53][2],s[54][2],s[55][2],s[56][2],s[57][2],s[58][2],s[59][2]);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",s[0][3],s[1][3],s[2][3],s[3][3],s[4][3],s[5][3],s[6][3],s[7][3],s[8][3],s[9][3],s[10][3],s[11][3],s[12][3],s[13][3],s[14][3],s[15][3],s[16][3],s[17][3],s[18][3],s[19][3],s[20][3],s[21][3],s[22][3],s[23][3],s[24][3],s[25][3],s[26][3],s[27][3],s[28][3],s[29][3],s[30][3],s[31][3],s[32][3],s[33][3],s[34][3],s[35][3],s[36][3],s[37][3],s[38][3],s[39][3],s[40][3],s[41][3],s[42][3],s[43][3],s[44][3],s[45][3],s[46][3],s[47][3],s[48][3],s[49][3],s[50][3],s[51][3],s[52][3],s[53][3],s[54][3],s[55][3],s[56][3],s[57][3],s[58][3],s[59][3]);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",s[0][4],s[1][4],s[2][4],s[3][4],s[4][4],s[5][4],s[6][4],s[7][4],s[8][4],s[9][4],s[10][4],s[11][4],s[12][4],s[13][4],s[14][4],s[15][4],s[16][4],s[17][4],s[18][4],s[19][4],s[20][4],s[21][4],s[22][4],s[23][4],s[24][4],s[25][4],s[26][4],s[27][4],s[28][4],s[29][4],s[30][4],s[31][4],s[32][4],s[33][4],s[34][4],s[35][4],s[36][4],s[37][4],s[38][4],s[39][4],s[40][4],s[41][4],s[42][4],s[43][4],s[44][4],s[45][4],s[46][4],s[47][4],s[48][4],s[49][4],s[50][4],s[51][4],s[52][4],s[53][4],s[54][4],s[55][4],s[56][4],s[57][4],s[58][4],s[59][4]);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",s[0][5],s[1][5],s[2][5],s[3][5],s[4][5],s[5][5],s[6][5],s[7][5],s[8][5],s[9][5],s[10][5],s[11][5],s[12][5],s[13][5],s[14][5],s[15][5],s[16][5],s[17][5],s[18][5],s[19][5],s[20][5],s[21][5],s[22][5],s[23][5],s[24][5],s[25][5],s[26][5],s[27][5],s[28][5],s[29][5],s[30][5],s[31][5],s[32][5],s[33][5],s[34][5],s[35][5],s[36][5],s[37][5],s[38][5],s[39][5],s[40][5],s[41][5],s[42][5],s[43][5],s[44][5],s[45][5],s[46][5],s[47][5],s[48][5],s[49][5],s[50][5],s[51][5],s[52][5],s[53][5],s[54][5],s[55][5],s[56][5],s[57][5],s[58][5],s[59][5]);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",s[0][6],s[1][6],s[2][6],s[3][6],s[4][6],s[5][6],s[6][6],s[7][6],s[8][6],s[9][6],s[10][6],s[11][6],s[12][6],s[13][6],s[14][6],s[15][6],s[16][6],s[17][6],s[18][6],s[19][6],s[20][6],s[21][6],s[22][6],s[23][6],s[24][6],s[25][6],s[26][6],s[27][6],s[28][6],s[29][6],s[30][6],s[31][6],s[32][6],s[33][6],s[34][6],s[35][6],s[36][6],s[37][6],s[38][6],s[39][6],s[40][6],s[41][6],s[42][6],s[43][6],s[44][6],s[45][6],s[46][6],s[47][6],s[48][6],s[49][6],s[50][6],s[51][6],s[52][6],s[53][6],s[54][6],s[55][6],s[56][6],s[57][6],s[58][6],s[59][6]);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",s[0][7],s[1][7],s[2][7],s[3][7],s[4][7],s[5][7],s[6][7],s[7][7],s[8][7],s[9][7],s[10][7],s[11][7],s[12][7],s[13][7],s[14][7],s[15][7],s[16][7],s[17][7],s[18][7],s[19][7],s[20][7],s[21][7],s[22][7],s[23][7],s[24][7],s[25][7],s[26][7],s[27][7],s[28][7],s[29][7],s[30][7],s[31][7],s[32][7],s[33][7],s[34][7],s[35][7],s[36][7],s[37][7],s[38][7],s[39][7],s[40][7],s[41][7],s[42][7],s[43][7],s[44][7],s[45][7],s[46][7],s[47][7],s[48][7],s[49][7],s[50][7],s[51][7],s[52][7],s[53][7],s[54][7],s[55][7],s[56][7],s[57][7],s[58][7],s[59][7]);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",s[0][8],s[1][8],s[2][8],s[3][8],s[4][8],s[5][8],s[6][8],s[7][8],s[8][8],s[9][8],s[10][8],s[11][8],s[12][8],s[13][8],s[14][8],s[15][8],s[16][8],s[17][8],s[18][8],s[19][8],s[20][8],s[21][8],s[22][8],s[23][8],s[24][8],s[25][8],s[26][8],s[27][8],s[28][8],s[29][8],s[30][8],s[31][8],s[32][8],s[33][8],s[34][8],s[35][8],s[36][8],s[37][8],s[38][8],s[39][8],s[40][8],s[41][8],s[42][8],s[43][8],s[44][8],s[45][8],s[46][8],s[47][8],s[48][8],s[49][8],s[50][8],s[51][8],s[52][8],s[53][8],s[54][8],s[55][8],s[56][8],s[57][8],s[58][8],s[59][8]);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",s[0][9],s[1][9],s[2][9],s[3][9],s[4][9],s[5][9],s[6][9],s[7][9],s[8][9],s[9][9],s[10][9],s[11][9],s[12][9],s[13][9],s[14][9],s[15][9],s[16][9],s[17][9],s[18][9],s[19][9],s[20][9],s[21][9],s[22][9],s[23][9],s[24][9],s[25][9],s[26][9],s[27][9],s[28][9],s[29][9],s[30][9],s[31][9],s[32][9],s[33][9],s[34][9],s[35][9],s[36][9],s[37][9],s[38][9],s[39][9],s[40][9],s[41][9],s[42][9],s[43][9],s[44][9],s[45][9],s[46][9],s[47][9],s[48][9],s[49][9],s[50][9],s[51][9],s[52][9],s[53][9],s[54][9],s[55][9],s[56][9],s[57][9],s[58][9],s[59][9]);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",s[0][10],s[1][10],s[2][10],s[3][10],s[4][10],s[5][10],s[6][10],s[7][10],s[8][10],s[9][10],s[10][10],s[11][10],s[12][10],s[13][10],s[14][10],s[15][10],s[16][10],s[17][10],s[18][10],s[19][10],s[20][10],s[21][10],s[22][10],s[23][10],s[24][10],s[25][10],s[26][10],s[27][10],s[28][10],s[29][10],s[30][10],s[31][10],s[32][10],s[33][10],s[34][10],s[35][10],s[36][10],s[37][10],s[38][10],s[39][10],s[40][10],s[41][10],s[42][10],s[43][10],s[44][10],s[45][10],s[46][10],s[47][10],s[48][10],s[49][10],s[50][10],s[51][10],s[52][10],s[53][10],s[54][10],s[55][10],s[56][10],s[57][10],s[58][10],s[59][10]);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",s[0][11],s[1][11],s[2][11],s[3][11],s[4][11],s[5][11],s[6][11],s[7][11],s[8][11],s[9][11],s[10][11],s[11][11],s[12][11],s[13][11],s[14][11],s[15][11],s[16][11],s[17][11],s[18][11],s[19][11],s[20][11],s[21][11],s[22][11],s[23][11],s[24][11],s[25][11],s[26][11],s[27][11],s[28][11],s[29][11],s[30][11],s[31][11],s[32][11],s[33][11],s[34][11],s[35][11],s[36][11],s[37][11],s[38][11],s[39][11],s[40][11],s[41][11],s[42][11],s[43][11],s[44][11],s[45][11],s[46][11],s[47][11],s[48][11],s[49][11],s[50][11],s[51][11],s[52][11],s[53][11],s[54][11],s[55][11],s[56][11],s[57][11],s[58][11],s[59][11]);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",s[0][12],s[1][12],s[2][12],s[3][12],s[4][12],s[5][12],s[6][12],s[7][12],s[8][12],s[9][12],s[10][12],s[11][12],s[12][12],s[13][12],s[14][12],s[15][12],s[16][12],s[17][12],s[18][12],s[19][12],s[20][12],s[21][12],s[22][12],s[23][12],s[24][12],s[25][12],s[26][12],s[27][12],s[28][12],s[29][12],s[30][12],s[31][12],s[32][12],s[33][12],s[34][12],s[35][12],s[36][12],s[37][12],s[38][12],s[39][12],s[40][12],s[41][12],s[42][12],s[43][12],s[44][12],s[45][12],s[46][12],s[47][12],s[48][12],s[49][12],s[50][12],s[51][12],s[52][12],s[53][12],s[54][12],s[55][12],s[56][12],s[57][12],s[58][12],s[59][12]);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",s[0][13],s[1][13],s[2][13],s[3][13],s[4][13],s[5][13],s[6][13],s[7][13],s[8][13],s[9][13],s[10][13],s[11][13],s[12][13],s[13][13],s[14][13],s[15][13],s[16][13],s[17][13],s[18][13],s[19][13],s[20][13],s[21][13],s[22][13],s[23][13],s[24][13],s[25][13],s[26][13],s[27][13],s[28][13],s[29][13],s[30][13],s[31][13],s[32][13],s[33][13],s[34][13],s[35][13],s[36][13],s[37][13],s[38][13],s[39][13],s[40][13],s[41][13],s[42][13],s[43][13],s[44][13],s[45][13],s[46][13],s[47][13],s[48][13],s[49][13],s[50][13],s[51][13],s[52][13],s[53][13],s[54][13],s[55][13],s[56][13],s[57][13],s[58][13],s[59][13]);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",s[0][14],s[1][14],s[2][14],s[3][14],s[4][14],s[5][14],s[6][14],s[7][14],s[8][14],s[9][14],s[10][14],s[11][14],s[12][14],s[13][14],s[14][14],s[15][14],s[16][14],s[17][14],s[18][14],s[19][14],s[20][14],s[21][14],s[22][14],s[23][14],s[24][14],s[25][14],s[26][14],s[27][14],s[28][14],s[29][14],s[30][14],s[31][14],s[32][14],s[33][14],s[34][14],s[35][14],s[36][14],s[37][14],s[38][14],s[39][14],s[40][14],s[41][14],s[42][14],s[43][14],s[44][14],s[45][14],s[46][14],s[47][14],s[48][14],s[49][14],s[50][14],s[51][14],s[52][14],s[53][14],s[54][14],s[55][14],s[56][14],s[57][14],s[58][14],s[59][14]);
}

int end(int score)
{
    for(int sp=60;sp>10;sp+=-1){
        cls();
        space(sp); printf(" ██████╗  █████╗ ███╗   ███╗███████╗\n");
        space(sp); printf("██╔════╝ ██╔══██╗████╗ ████║██╔════╝\n");
        space(sp); printf("██║  ███╗███████║██╔████╔██║█████╗  \n");
        space(sp); printf("██║   ██║██╔══██║██║╚██╔╝██║██╔══╝  \n");
        space(sp); printf("╚██████╔╝██║  ██║██║ ╚═╝ ██║███████╗\n");
        space(sp); printf(" ╚═════╝ ╚═╝  ╚═╝╚═╝     ╚═╝╚══════╝\n");
        space(sp); printf("                                    \n");
        space(sp); printf(" ██████╗ ██╗   ██╗███████╗██████╗   \n");
        space(sp); printf("██╔═══██╗██║   ██║██╔════╝██╔══██╗  \n");
        space(sp); printf("██║   ██║██║   ██║█████╗  ██████╔╝  \n");
        space(sp); printf("██║   ██║╚██╗ ██╔╝██╔══╝  ██╔══██╗  \n");
        space(sp); printf("╚██████╔╝ ╚████╔╝ ███████╗██║  ██║  \n");
        space(sp); printf(" ╚═════╝   ╚═══╝  ╚══════╝╚═╝  ╚═╝  \n");

        delay(30);
    }
    printf("\n                     Score: %d\n\n              Press [ENTER] to replay, [Q]+[ENTER] to leave\n",score);
}
int endz(int score)
{
    for(int sp=60;sp>10;sp+=-1){
        cls();
        space(sp); printf(" ██████╗  █████╗ ███╗   ███╗███████╗\n");
        space(sp); printf("██╔════╝ ██╔══██╗████╗ ████║██╔════╝\n");
        space(sp); printf("██║  ███╗███████║██╔████╔██║█████╗  \n");
        space(sp); printf("██║   ██║██╔══██║██║╚██╔╝██║██╔══╝  \n");
        space(sp); printf("╚██████╔╝██║  ██║██║ ╚═╝ ██║███████╗\n");
        space(sp); printf(" ╚═════╝ ╚═╝  ╚═╝╚═╝     ╚═╝╚══════╝\n");
        space(sp); printf("                                    \n");
        space(sp); printf(" ██████╗ ██╗   ██╗███████╗██████╗   \n");
        space(sp); printf("██╔═══██╗██║   ██║██╔════╝██╔══██╗  \n");
        space(sp); printf("██║   ██║██║   ██║█████╗  ██████╔╝  \n");
        space(sp); printf("██║   ██║╚██╗ ██╔╝██╔══╝  ██╔══██╗  \n");
        space(sp); printf("╚██████╔╝ ╚████╔╝ ███████╗██║  ██║  \n");
        space(sp); printf(" ╚═════╝   ╚═══╝  ╚══════╝╚═╝  ╚═╝  \n");

        delay(30);
    }
    printf("\n                     分數: %d\n\n              按下 [ENTER] 鍵以重玩遊戲，[Q]+[ENTER]以離開遊戲\n",score);
}

// game loader
int game(int lg)
{
    //config
    int tps= 50 ;
    int life= 1 ;
    int score= 0 ;

    //init
    int s[100][150];
    int t[100][150];
    int dt,tick,a,ret,tk1,y,xs,xs1,xs2,xs3,xs4,xsorg,xx1,xx2,xx3,xx4,x,x2,dt2,dt3,dt4,d,location,repeat;
    fd_set read_fds;
    struct timeval timeout;
    char c;
    int mv=10;int xt1=0;int xt2=0;int xt3=0;int xt4=0;int loop=0;int die=0;
    
    cls();

    // MAIN game loop
    for(int i=1; i>0; i++){
        tick = i;

        // control init
        FD_ZERO(&read_fds);
        FD_SET(0, &read_fds);
        timeout.tv_sec = 0;
        timeout.tv_usec = 0;
        ret = select(1, &read_fds, NULL, NULL, &timeout);
        if (ret == -1) {
            perror("select");
            return 1;
        } else if (ret > 0) {
            if (FD_ISSET(0, &read_fds)) {
                // input
                a = key();
                // enter=break
                if(a==3) {return score;}
            }
        }

        // dick movement
        if(a==5){
            mv+=-1;
            if(mv<0){mv=0;}
        } else if(a==7){
            mv++;
            if(mv>13){mv=13;}
        }

        // shoot
        if(a==4){
            location=mv*4+5;
            repeat=5;
        }

        // missle control
        dt = (tick/10)%15;
        dt2 = ((tick-30)/10)%15;
        dt3 = ((tick-60)/10)%15;
        dt4 = ((tick-90)/10)%15;

        tk1 = tick%150;

        if(tk1==0){
            srand( time(NULL) );
            xs=rand();
        }
        else if(tk1==1){
            srand( time(NULL)*2 );
            xs1=rand()%59;
            xt1=0;
        }
        else if(tk1==30){
            srand( time(NULL)*3 );
            xs2=rand()%59;
            xt2=0;
        }
        else if(tk1==60){
            srand( time(NULL)*4 );
            xs3=rand()%59;
            xt3=0;
        }
        else if(tk1==90){
            srand( time(NULL)*5 );
            xs4=rand()%59;
            xt4=0;
        }

        //init
        for(x=0;x<=60;x++){
            for(y=0;y<15;y++){
                s[x][y]=32;
            }
        }

        //got shot
        xx1='#';xx2='#';xx3='#';xx4='#';
        
        if(repeat==5){
            if((abs(xs1-location)<2) && (xt1==0)){ score++; }
            if((abs(xs2-location)<2) && (xt2==0)){ score++; }
            if((abs(xs3-location)<2) && (xt3==0)){ score++; }
            if((abs(xs4-location)<2) && (xt4==0)){ score++; }
        }
        if(repeat>0){
            //laser
            for(int o=0;o<15;o++){
                s[location][o]='#';
            }
            //disappear
            if(abs(xs1-location)<2){
                xt1=1;
            }
            if(abs(xs2-location)<2){
                xt2=1;
            }
            if(abs(xs3-location)<2){
                xt3=1;
            }
            if(abs(xs4-location)<2){
                xt4=1;
            }
        }


        if(xt1==1){
            xx1=32;
        } else {
            xx1='#';
        }
        if(xt2==1){
            xx2=32;
        } else {
            xx2='#';
        }
        if(xt3==1){
            xx3=32;
        } else {
            xx3='#';
        }
        if(xt4==1){
            xx4=32;
        } else {
            xx4='#';
        }

        s[xs1][dt+1]=xx1;
        s[xs1-1][dt]=xx1;
        s[xs1][dt]=xx1;
        s[xs1+1][dt]=xx1;

        s[xs2][dt2+1]=xx2;
        s[xs2][dt2]=xx2;
        s[xs2-1][dt2]=xx2;
        s[xs2+1][dt2]=xx2;

        s[xs3][dt3+1]=xx3;
        s[xs3][dt3]=xx3;
        s[xs3+1][dt3]=xx3;
        s[xs3-1][dt3]=xx3;

        s[xs4][dt4+1]=xx4;
        s[xs4][dt4]=xx4;
        s[xs4+1][dt4]=xx4;
        s[xs4-1][dt4]=xx4;

        // die
        d = (mv*4)+5;
        if((dt==14) && (abs(xs1-d)<=2) && (xt1==0)){
            die=1;
        }
        else if((dt2==14) && (abs(xs2-d)<=2) && (xt2==0)){
            die=1;
        }
        else if((dt3==14) && (abs(xs3-d)<=2) && (xt3==0)){
            die=1;
        }
        else if((dt4==14) && (abs(xs4-d)<=2) && (xt4==0)){
            die=1;
        }

        
        if(die==1){
            die=0;
            life+=-1;
            if(life<=0){
                delay(100);
                return score;
            }
        }
        // main game render
        cls();
        if(lg==1){
            display(life,score,i,tps);
        }
        else if(lg==2){
            displayz(life,score,i,tps);
        }
        render_screen(s);
        render_dick(mv);

        // reset key
        a=0;
        repeat+=-1;

        // time.sleep
        //speed up
        if(tick<1000){
        delay(1000/tps);
        }
        else if(tick<2000){
            delay(900/tps);
        }
        else if(tick<2500){
            delay(800/tps);
        }
        else if(tick<3000){
            delay(700/tps);
        }
        else if(tick<4000){
            delay(600/tps);
        }
        else if(tick<5000){
            delay(500/tps);
        }
        else if(tick<10000){
            delay(300/tps);
        }
        else if(tick<50000){
            delay(200/tps);
        }
        // tick = 50000
        else{
            return 999999999;
        }
    }

}


// MAIN LOADER
int main()
{
    int c,score,lan,loop,mainloop;
    mainloop=1;
    cls();

        /*start*/
    lan = start();
        //en
    if(lan==1){
        loading();
        tutorial();
    }
    //zh
    else if(lan==2){
        loadingz();
        tutorialz();
    }

    // MAIN LOOP
    while (mainloop==1)
    {
        loop=1;
        if(lan==1){
            score = game(1);
            end(score);
        }
        else if(lan==2){
            score = game(2);
            endz(score);
        }
        while(loop==1){
            c=key();
            if(c==3){loop=0;}
            else if(c==1){mainloop=0;}
        }
        
    }
    if(lan==1){
        printf("\n\nQUITING...\nHave a nice day!\n\n> ");
    }
    else if(lan==2){
        printf("\n\n遊戲結束...\n祝您有個美好的一天!\n\n> ");
    }
    return 69;
}