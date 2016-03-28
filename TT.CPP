/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
/* Project Name: Prototype Model TTv122504 : Typing Tutor Program         */
/* Coded by    : Arman (a.k.a mindhack++) and The Super Friends           */
/* SubjectCode : A Sample Project of CSC133 Compiler Design               */
/* Project Consultant : Mr. Francis Baylon                                */
/* Note : This program is for educational purposes only.                  */
/*          You can free to use and modify this code                      */
/*          but i hope that you can learn new ideas from this.            */
/* sharing of knowledge is the greatest gift of mankind....               */

#include <time.h>
#include <stdio.h>
#include <graphics.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>
#include <dos.h>
#include <stdlib.h>
        /* CONSTANT VARIABLES */
#define TRUE 1
#define FALSE 0
#define ESC 27
#define BACKSPACE 8
#define ARROWUP 72
#define ARROWDOWN 80
#define GOINGLEFT 1
#define GOINGDOWN 2
#define GOINGRIGHT 3
#define MAX 550

        /* METHODS */
void initgraphix(void);
void destroygraphix(void);
void flashintro(void);
void fade(int r,int g,int b,int x,int y,char *string);
void fadewhitebar(int left,int top,int right,int bottom);
void signIn(void);
int  startType(void);
void initLesson(void);
void getrandomLesson(void);
int  getlessonSelected(void);
void displaylesson(void);
void openLesson(void);
void highlightLesson(int selectedlesson);
void decryptLesson(void);
void loadLesson(void);
void evaltypedlesson(void);
void popup(void);
void showAbout(void);
void displaySummary(void);
void savedtypingskillsResults(void);
void viewtypingskillsResults(void);
void fillBackgroundColor(int color);
void display_atik_atik_Menu(void);
void displaymenuLesson(void);
void displayHeadernFooter(void);
void typewriter_effects(char *contentmsg,int d);
void drawbox(int left,int top,int right,int bottom,int color);
void box1(int left,int top,int right,int bottom,int opendirection,int shadecolor,int mydelay);
void highlightChoice1(int selectedChoice);
int getChoice(void);
         /* GLOBAL VARIABLES */
void displayMenu(void);
void displaymenu(void);

int choiceID;
int starty=18;
int startx=29;

int key = 1234;             /* key */
char name[20];
char *username;
char *userprofiles;         /* saved the typing skills summary of the users */
struct  time t;             /* holds system time and date */

char lesson[MAX];
char decryptedlesson[MAX];
char typedlesson[MAX];
char lessonname[20];
char filename[20] = "mindhack";
FILE *fp;
FILE *login;

int totalchartyped = 0;         /* TOTAL CHARACTERS */
int totalerrors = 0;            /* TOTAL CHARACTERS ERROR TYPED */
int totalcorrect = 0;           /* TOTAL CHARACTERS CORRECT TYPED */
time_t starttime, endtime, xtime;
double typeaccuracy = 0.0;
double CPS;
double CPM;
double WPM;

void main(){
int choice ;
int done = FALSE;
char *t;

 flashintro();
 highvideo();
 textmode(64);
 signIn();                  /* sign in the user */
 for(;;){
 choiceID = 1;
    display_atik_atik_Menu();
    choice = getChoice();       /* get the user choice */
    switch(choice){
      case 1:
       for(;;) {
  displaymenuLesson();
   choice = getlessonSelected(); /* return the selected lesson */
   if (choice == -1) {
      box1(10,5,78,40,GOINGDOWN,BLUE,10);   /* erase-content container */
      break;
   }
   else {
     switch(choice){
       case 1:
         strcpy(filename,"numbers.enc");
         strcpy(lessonname,"All about numbers");
         break;
       case 2:
         strcpy(filename,"alphanum.enc");
         strcpy(lessonname,"Letters & Digits");
         break;
       case 3:
         strcpy(filename,"cybrmy.enc");
         strcpy(lessonname,"What's CyberArmy?");
         break;
       case 4:
         strcpy(filename,"poem.enc");
         strcpy(lessonname,"Short Poem");
         break;
       case 5:
         strcpy(filename,"complex.enc");
         strcpy(lessonname,"Complex Message");
       case 6:
         break;
       default:
         highlightLesson(choiceID);
     }// end switch(choice)
    openLesson();        /* open the lesson from external file */
    decryptLesson();     /* decrypt the encrypted lesson file */
    loadLesson();        /* take practice lesson */
    done = startType();  /* begin the user to type here        */
    if (done) {          /* if he done typing...*/
      evaltypedlesson();   /* evaluate the users typing skills */
      displaySummary();    /* display the typing skills summary */
      savedtypingskillsResults(); /* save the typing skills summary to textfiles*/
    }
   }//endelse
       }//endfor
       break;
      case 2:
       showAbout();       /* show about this software... */
       break;
      case 3:
       fcloseall();      /* close all open streams */
       exit(0);          /* quit program      */
       break;
      case 4:
       break;
      case 5:
       break;
  }  /* endswitch*/
 }/* endfor */
}/* endmain */


/* ------------------ DISPLAY FLASH INTRO kunuhay ra ----------------*/
void flashintro(void) {
int midx,midy,x1,x2;
int c;
int bottom,bottom2;
int top;
int left;
int a,b;
int r;

   initgraphix();
   char p[8] =   { 0x00, 0x00, 0x22, 0x08, 0x00, 0x22, 0x08, 0x00 };
   //char p2[8] =   { 0x00, 0x10, 0x10, 0x7C, 0x10, 0x10, 0x00, 0x00 };

   delay(1000);
   for(bottom = getmaxy(),bottom2 = 0;
  bottom>=400 ,bottom2<=getmaxy()-400; bottom--,bottom2++){
     setfillstyle(1,DARKGRAY);
     bar(0,0,getmaxx(),bottom2);            /* TOP BAR    */
     bar(0,getmaxy(),getmaxx(),bottom);     /* BOTTOM BAR */
     delay(5);
   }
   setcolor(WHITE);
   line(0,400,getmaxx(),400);                     /* BOTTOM LINE */
   line(0,getmaxy()-400,getmaxx(),getmaxy()-400); /* TOP LINE    */

   fadewhitebar(0,getmaxy()-400,getmaxx(),400); /* PUT SPLASH WHITE HERE..LATER */
   destroygraphix();

   initgraphix();
   setbkcolor(BLUE);

   setfillpattern(p,LIGHTBLUE);
   bar(0,getmaxy()-400,getmaxx(),400);    /* MIDDLE BAR */

   setfillstyle(1,DARKGRAY);
   bar(0,0,getmaxx(),getmaxy()-400);        /* TOP BAR    */
   bar(0,getmaxy(),getmaxx(),400);          /* BOTTOM BAR */

   setcolor(WHITE);
   line(0,400,getmaxx(),400);                     /* BOTTOM LINE */
   line(0,getmaxy()-400,getmaxx(),getmaxy()-400); /* TOP LINE    */
   setfillstyle(1,DARKGRAY);
   for(r=210; r<=430; r++){
       bar(210,175,r,250);
       delay(3);                       /* CENTER BAR */
   }
   setfillstyle(1,GREEN);

   setcolor(WHITE);
   setlinestyle(2,1,1);
   rectangle(210,175,430,250);
           /* BOX REPLICATION */
   bar(215,180,245,210); /* C */
   bar(245,215,275,245); /* E */
   bar(275,180,305,210); /* R */
   bar(305,215,335,245); /* W */
   bar(335,180,365,210); /* O */
   bar(365,215,395,245); /* R */
   bar(395,180,425,210); /* N */
   delay(100);

   settextstyle(2,HORIZ_DIR,4);
   outtextxy(10,65,"..\\version 12.25.2004\\..");
   outtextxy(getmaxx()-150,400,"..\\coded by mh \\..");
   settextstyle(12,HORIZ_DIR,0);
   setcolor(0);
   outtextxy(228,190,"T");delay(100);
   setcolor(YELLOW);
   outtextxy(225+33,188+2,"Y");delay(100);
   setcolor(LIGHTMAGENTA);
   outtextxy(225+63,188+2,"P");delay(100);
   setcolor(LIGHTRED);
   outtextxy(225+93,188+2,"I");delay(100);
   setcolor(WHITE);
   outtextxy(225+123,188+2,"N");delay(100);
   setcolor(YELLOW);
   outtextxy(225+153,188+2,"G");delay(100);
   setcolor(LIGHTBLUE);
   outtextxy(225+180,188+2,"/");delay(100);
   setcolor(GREEN);
   outtextxy(225,188+35,"");delay(100);
   setcolor(LIGHTMAGENTA);
   outtextxy(225+33,188+35+2,"T");delay(100);
   setcolor(LIGHTRED);
   outtextxy(225+63,188+35+2,"U");delay(100);
   setcolor(WHITE);
   outtextxy(225+93,188+35+2,"T");delay(100);
   setcolor(YELLOW);
   outtextxy(225+123,188+35+2,"O");delay(100);
   setcolor(WHITE);
   outtextxy(225+153,188+35+2,"R");delay(100);
   setcolor(LIGHTGREEN);
   outtextxy(225+183,188+35+2,"");delay(100);
   delay(10);
   setcolor(WHITE);
   nosound();
   while(1){
  if (kbhit()){
     c = getch();
     if (c == ESC ) exit(0);
     else break;
  }
  settextstyle(2,HORIZ_DIR,4);
  setcolor(LIGHTGREEN);

  outtextxy(getmaxx()/2-70,410,"® press key to continue ¯");
  delay(90);

  setcolor(DARKGRAY);
  outtextxy(getmaxx()/2-70,410,"® press key to continue ¯");
  delay(90);
  }
   //getch();
   //exit(0);
   destroygraphix();
   restorecrtmode();
   box1(1,1,80,50,GOINGDOWN,RED,0);      /* bottom box */
   box1(2,2,79,49,GOINGDOWN,BROWN,0);    /* middle box */
   box1(3,3,78,48,GOINGDOWN,BLUE,0);     /* top box */

}

/* --------------------- FADE IN/OUT WHITE PLANE -------------------------*/
void fadewhitebar(int left,int top,int right,int bottom){
   struct palettetype pal;
   int i, ht, y, xmax;

   delay(500);
   /* grab a copy of the palette */
   getpalette(&pal);

   /* create gray scale */
   for (i=0; i<pal.size; i++)
      setrgbpalette(pal.colors[i], i*4, i*4, i*4);

   /* display the gray scale */
   ht = getmaxy() / 16;
   y = 0;
   for (i=0; i<pal.size; i++)
   {
      setfillstyle(SOLID_FILL, i);
      bar(left,top,right,bottom);
      y += ht;delay(10);
   }

    for (i=pal.size;i>1; i--)
   {
      setfillstyle(SOLID_FILL, i);
      bar(left,top,right,bottom);
      y += ht;delay(10);
   }
}

/* ----------------- DISPLAY MENU wid TYPEWRITER EFFECTS --------------------*/
void display_atik_atik_Menu(void){
char str[9],str1[20],str2[9];
char dest[10];

   _setcursortype(_NOCURSOR);
   box1(5,5,74,11,GOINGDOWN,BROWN,20);   /* container */
   box1(5,5,76,13,GOINGLEFT,BLACK,0); /* header drop shadow */
   box1(5,5,74,11,GOINGLEFT,BROWN,0); /* header container */
   drawbox(5,5,74,11,YELLOW);
   textcolor(WHITE);
   gotoxy(7,6); cprintf("Hi ");textcolor(LIGHTGREEN);cprintf("%s!",username);
   textcolor(WHITE);
   gotoxy(7,7); typewriter_effects("Welcome to Typing Tutor Program",5);
   gotoxy(15,9); typewriter_effects("It has been a while since your last practice session. ",5);
   gotoxy(15,10); typewriter_effects("It is good to have you back to improve your typing skills.",5);

   box1(26,14,56,16,GOINGLEFT,YELLOW,6); /* container */
   box1(26,14,58,23,GOINGLEFT,0,0);      /* menu dropshadow */
   box1(26,14,56,16,GOINGLEFT,YELLOW,0); /* container */
   drawbox(26,14,56,16,YELLOW);
   textcolor(WHITE);gotoxy(29,15);cprintf(".: What do you want ? :.");
   box1(26,17,56,17+4,GOINGDOWN,YELLOW,10); /* menu container */
   box1(26,17,56,17+4,GOINGDOWN,YELLOW,0); /* menu container */
   drawbox(26,17,56,17+4,YELLOW);
   textcolor(LIGHTCYAN);
   gotoxy(startx,starty);typewriter_effects("þ Take a practice lesson þ",5);
   gotoxy(startx,starty+1);typewriter_effects("þ Know the developers    þ",5);
   gotoxy(startx,starty+2);typewriter_effects("þ Exit                   þ",5);

  textbackground(BLUE);
  strcpy(str1,"Today's date : ");
  strcat(str1, _strdate(str));
  gotoxy(7,47); textcolor(WHITE);typewriter_effects(str1,10);
  textcolor(YELLOW);gotoxy(37,47);typewriter_effects("Use arrow keys to move the selection...",10);
}

/* ----------------DISPLAY MENU LESSON  :D ------------------------------*/
void displaymenuLesson(void) {
   box1(4,3,78,13,GOINGDOWN,BLUE,10); /* erase-header container */
   box1(24,13,60,30,GOINGDOWN,BLUE,10); /* erase - menu container */

   box1(26,15,57,23,GOINGLEFT,YELLOW,6); /* content container */
   box1(26,15,59,25,GOINGLEFT,BLACK,0); /* drop shadow content container */
   box1(26,15,57,23,GOINGLEFT,YELLOW,0); /* content container */
   drawbox(26,15,57,23,YELLOW);

   drawbox(26,15,57,17,YELLOW);

   textcolor(WHITE);
   gotoxy(startx-2,starty-2);cprintf("What lesson you want to take?");
   textcolor(LIGHTCYAN);
   gotoxy(startx-2,starty);cprintf("þ Lesson1: All about Numbers þ");
   gotoxy(startx-2,starty+1);cprintf("þ Lesson2: Letters and Digitsþ");
   gotoxy(startx-2,starty+2);cprintf("þ Lesson3: What's CyberArmy? þ");
   gotoxy(startx-2,starty+3);cprintf("þ Lesson4: Short Poem        þ");
   gotoxy(startx-2,starty+4);cprintf("þ Lesson5: Complex Message   þ");
   gotoxy(37,47);textbackground(BLUE);
   textcolor(YELLOW); cprintf("Press ESC to back to Main Menu...        ");

   gotoxy(7,47); textcolor(WHITE); cprintf("                          ");
}


/* ------------------------- DISPLAY THE MENU ------------------------------*/
void displaymenu(void){
   textcolor(LIGHTCYAN);
   textbackground(BROWN);
   gotoxy(startx,starty);cprintf("þ Take a practice lesson þ");
   gotoxy(startx,starty+1);cprintf("þ Know the developers    þ");
   gotoxy(startx,starty+2);cprintf("þ Exit                   þ");
}
/* ---------------------- DISPLAY THE LESSON MENU -------------------------*/
void displaylesson(void){
   textcolor(LIGHTCYAN);
   textbackground(BROWN);
   gotoxy(startx-2,starty);cprintf("þ Lesson1: All about Numbers þ");
   gotoxy(startx-2,starty+1);cprintf("þ Lesson2: Letters and Digitsþ");
   gotoxy(startx-2,starty+2);cprintf("þ Lesson3: What's CyberArmy? þ");
   gotoxy(startx-2,starty+3);cprintf("þ Lesson4: Short Poem        þ");
   gotoxy(startx-2,starty+4);cprintf("þ Lesson5: Complex Message   þ");
}

/* -------------------- DISPLAY THE POP UP TEXT  ---------------------------*/
void popup(void){
box1(10,25,75,40,GOINGRIGHT,BLUE,4); /* erase the popup text */
   switch(choiceID){
  case 1:
    box1(12,29,72,32,GOINGLEFT,BROWN,3);
    drawbox(12,29,72,32,YELLOW); textcolor(WHITE);
    gotoxy(13,30);cprintf("This section contain a set of numbers in which you");delay(50);
    gotoxy(13,31);cprintf("can enhance your typing using the keypad on your keyboard.");delay(50);
    break;
  case 2:
    box1(12,29,72,32,GOINGLEFT,BROWN,3);
    drawbox(12,29,72,32,YELLOW); textcolor(WHITE);
    gotoxy(13,30);cprintf(" This section contain a set of words followed with a");delay(50);
    gotoxy(13,31);cprintf(" numbers. For example, kemper108, hello123, etc...");delay(50);
    break;
  case 3:
    box1(12,29,72,32,GOINGLEFT,BROWN,3);
    drawbox(12,29,72,32,YELLOW); textcolor(WHITE);
    gotoxy(13,30);cprintf(" This section contain a short paragraph that talks about");delay(50);
    gotoxy(13,31);cprintf("  CyberArmy and their purpose on the internet...");delay(50);
    break;
  case 4:
    box1(12,29,72,32,GOINGLEFT,BROWN,3);
    drawbox(12,29,72,32,YELLOW); textcolor(WHITE);
    gotoxy(13,30);cprintf(" In this section present a very short poem that tells");delay(50);
    gotoxy(13,31);cprintf(" about a man can never be lived without a woman.");delay(50);
    break;
  case 5:
    box1(12,29,72,33,GOINGLEFT,BROWN,3);
    drawbox(12,29,72,33,YELLOW); textcolor(WHITE);
    gotoxy(13,30);cprintf("In this section. It talks about a person that had a dreamt.");delay(50);
    gotoxy(13,31);cprintf("His message contain a words combined with numbers and ");delay(50);
    gotoxy(13,32);cprintf("punctuations, operators, and lower/upper case characters.");delay(50);
    break;
   }
}

/* -------------------- TYPEWRITER TEXT EFFECTS ----------------------------*/
void typewriter_effects(char *contentmessage,int d){
char *p;
  p = contentmessage;/*POINTER p POINTS TO STARTING ADRESS OF d contentmessage*/
  while(*p) {
    cprintf("%c",*p);delay(d);*p++;
  }
}

/* ---------------------HIGHLIGHT THE SELECTED CHOICE----------------------*/
void highlightChoice1(int selectedChoice){
      textcolor(LIGHTGREEN);
      switch(selectedChoice){
   case 1:  gotoxy(startx,starty);cprintf("þ Take a practice lesson þ");
      break;
   case 2:  gotoxy(startx,starty+1);cprintf("þ Know the developers    þ");
      break;
   case 3:  gotoxy(startx,starty+2);cprintf("þ Exit                   þ");
      break;
      }
}
/* ----------------------HIGHLIGHT THE SELECTED LESSON----------------------*/
void highlightLesson(int selectedlesson){
      textcolor(LIGHTGREEN);
      switch(selectedlesson){
   case 1:  gotoxy(startx-2,starty);cprintf("þ Lesson1: All about Numbers þ");
      break;
   case 2:  gotoxy(startx-2,starty+1);cprintf("þ Lesson2: Letters and Digitsþ");
      break;
   case 3:  gotoxy(startx-2,starty+2);cprintf("þ Lesson3: What's CyberArmy? þ");
      break;
   case 4:  gotoxy(startx-2,starty+3);cprintf("þ Lesson4: Short Poem        þ");
      break;
   case 5:  gotoxy(startx-2,starty+4);cprintf("þ Lesson5: Complex Message   þ");
      break;
      }


}
/* --------------------- RETURN THE SELECTED CHOICE -----------------------*/
int getChoice(void){
int ch,i;

   displaymenu();
   highlightChoice1(choiceID);
   while(ch!=13){
     ch=getch();
     /*    printf("%d",ch); */
      switch(ch){
  case ARROWUP :                  /* arrow up */
          choiceID--;
          if (choiceID<1) {
        choiceID=3;
          }
           break;
  case ARROWDOWN :                /* arrow down */
           choiceID++;
           if (choiceID>3) {
       choiceID=1;
           }
           break;
     }
     displaymenu();
     highlightChoice1(choiceID);
  }
  return choiceID;
}
/* --------------------- RETURN THE SELECTED LESSON -----------------------*/
int getlessonSelected(void){
int ch;

   displaylesson();
   highlightLesson(choiceID);
   while(ch!=13){
     ch=getch();
     /*    printf("%d",ch); */
      switch(ch){
  case ESC     : ch = 13;
           choiceID = -1;
           break;
  case ARROWUP :                  /* arrow up */
          choiceID--;
          if (choiceID<1) {
       choiceID=5;
          }
           popup();
           break;
  case ARROWDOWN :                /* arrow down */
           choiceID++;
           if (choiceID>5) {
       choiceID=1;
           }
           popup();
           break;
     }

     displaylesson();
     highlightLesson(choiceID);

  }

  return choiceID;
}

/* --------------------- INIT AND DESTROY GRAPHICS MODE---------------------*/
void initgraphix(){
int gd=DETECT;   /* request auto detection */
int gm;
int errcode;
  initgraph(&gd,&gm,"..\\bgi");
  errcode=graphresult();
  if (errcode!=grOk){
      printf("Graphics error : %s.\n",grapherrormsg(errcode));
      getch();
      exit(1);
  }
}
void destroygraphix(){
  closegraph();
}

/* -----------------------SIGN THE USER NAME ------------------------------*/
void signIn(void) {
  delay(300);
  _setcursortype(_NOCURSOR);
  box1(28,14,52,20,GOINGLEFT,BROWN,15);  /* box         */
  box1(28,14,54,22,GOINGLEFT,BLACK,0);  /* drop shadow */
  box1(28,14,52,20,GOINGLEFT,BROWN,0);  /* box         */
  drawbox(28,14,52,20,YELLOW);
  drawbox(30,17,50,19,YELLOW);
  gotoxy(34,14); typewriter_effects(".: Sign In :.",5);
  gotoxy(30,16); textcolor(WHITE); typewriter_effects("Enter your name here:",9);
  name[0] = 10; gotoxy(31,18); textcolor(WHITE);
  _setcursortype(_NORMALCURSOR); username = cgets(name);

  if (strlen(username) == 0 ) {
     strcpy(username,"armano");
     strcpy(userprofiles,username);
  }
  strcpy(userprofiles,username);
  strcat(userprofiles,".txt");

  if ((login = fopen(username,"a+")) == NULL){
   gotoxy(7,6); cprintf("error in creating user %s",username);
   getch();
   exit(0);
  }

  _setcursortype(_NOCURSOR);
  box1(27,12,54,23,GOINGLEFT,BLUE,10);  /* erase box  */
}


/* ------- LOAD THE ENCRYPTED EXTERNAL FILE FROM THE SELECTED LESSON ------- */
void openLesson(void){
char ch;
    if ((fp = fopen(filename,"rb")) == NULL){
       gotoxy(1,1); cprintf("Cannot open a file %s",filename);
       getch();
       exit(0);
    }
}
/* ------------ DECRYPT THE ENCRYPTED LESSON FILE given the key ---------- */
void decryptLesson(void){
char ch;
int i=0;

    while((ch = fgetc(fp)) != EOF ){
   ch = ch ^ key;
   decryptedlesson[i++] = ch;
    }

    decryptedlesson[i++] = NULL;
    for(i=0; i<strlen(decryptedlesson); i++){
   if (decryptedlesson[i] == '#') {
     break;
   }
   else lesson[i] = decryptedlesson[i];
    }
    lesson[i] = NULL;
    fclose(fp);
}

/* ---------------- LOAD THE DECRYPTED LESSON FILE ------------------------*/
void loadLesson(void){
char buf[20];
char *p;
char dest[20];
int ch;
int len;
int rowCtr = 7;
int index = 0;
int xpos = 7;
int ypos = 7;
int lineNumber = 1;
int numkeystrokes = 0;

box1(10,5,78,40,GOINGDOWN,BLUE,10);   /* erase-content container */
textcolor(BLUE);textbackground(BLUE); /* hides the text fields */
gotoxy(30,47);cprintf("Note: Use arrow keys to move the selection....");
gotoxy(7,47);cprintf("Today's date                      ");

gotoxy(6,4);textcolor(WHITE);textbackground(BLUE);
cprintf("Lesson Name : %s",lessonname);
strcpy(dest,"Log in :"); strncat(dest,username,strlen(username));
gotoxy(50,4); typewriter_effects(dest,10);

box1(6,5,75,45,GOINGLEFT,LIGHTGREEN,5);/* content bkcolor */
box1(6,5,77,47,GOINGDOWN,0,0);        /* content drop shadow */
box1(6,5,75,45,GOINGDOWN,LIGHTGREEN,0);/* content bkcolor */
drawbox(6,5,75,45,YELLOW);

textbackground(GREEN);
textcolor(WHITE);

//gotoxy(1,1); cprintf("Please type here to load a text files:");
//scanf("%s",filename);
  len = strlen(lesson);
  while(index<=len){
    if (rowCtr>74) {
       ypos += 5;     /* STEP 1 LINE */
       rowCtr = 7;    /* RESET ROWCTR TO STARTING 7 */
       xpos = 7;
       lineNumber ++; /* INCREMENT THE LINE NUMBER */
    }
      ch = lesson[index];      /* check the characters if it is newlines */
      if (isspace(ch)){        /* or tabs, if they are, they will be */
    ch = ' ';            /* change into spaces to avoid any    */
      }                        /* further errors  :-)                 */
      lesson[index] = ch;
      numkeystrokes ++;
      index++;
      gotoxy(xpos,ypos);
      cprintf("%c",ch);
      rowCtr++;
      xpos++;
  }

  totalchartyped = numkeystrokes;
  gotoxy(40,47);textbackground(BLUE);
  textcolor(YELLOW); cprintf("Press ESC to back to Main Menu...");
  textbackground(GREEN);
}

/* --------------------------   TYPING MODULE  ----------------------------*/
int startType(void) {
int chrKey = 0;
int done;
register int i = 0;
int xpos = 7;
int ypos = 7;
int keys = 0;
int iscancelled = FALSE;

 delay(10);
 starttime = time(NULL);          /* start the timeR */
 while(keys<totalchartyped-1 && iscancelled!=TRUE){
  textcolor(WHITE);
  if (xpos>74) {
    xpos = 7; ypos +=5;
  }

  if (xpos>0) {
     gotoxy(xpos,ypos+1); textcolor(YELLOW);cprintf("");
  }

  textcolor(YELLOW); gotoxy(75,ypos+1); cprintf("³"); /* overwrites */
  textcolor(WHITE);
  gotoxy(xpos,ypos+1); chrKey = getch();
  typedlesson[keys] = chrKey; putchar(chrKey);
  switch(chrKey){
  case BACKSPACE :
        if (xpos == 7 && ypos>7) {
      gotoxy(7,ypos+1); cprintf(" ");
      xpos = 75;
      ypos -=5;

        }
        if (xpos>7) {
     xpos --; /* DECREMENT X LOCATION OF CURSOR*/
     i --;    /* DECREMENT lesson index */
     keys --;
     gotoxy(xpos,ypos+1); cprintf(" ");
     gotoxy(xpos,ypos-1); cprintf(" ");
     gotoxy(xpos+1,ypos+1); cprintf(" "); /* CLEAR THE  (31) */
        }
        break;
   case ESC :
        box1(5,4,76,48,GOINGRIGHT,BLUE,5);/* erase content bkcolor */
        iscancelled = TRUE;
        break;
   default:
        /* KUNG SAYOP ANG GI TYPE (kay nagdaghan si dodong ug si inday) */
        /* or dili lang gyud kahibalo mo type parehas nako! hehehe! Tsada! Bay! */
        if ((chrKey != lesson[i]) && (keys<totalchartyped)){
      textcolor(RED); gotoxy(xpos,ypos-1); cprintf("");
      gotoxy(xpos,ypos+1);cprintf("%c",chrKey);textcolor(WHITE);
        }
        else {
      gotoxy(xpos,ypos-1); cprintf(" ");
        }

              keys ++;
        i++;
              xpos++;
              break;

  }

 }

 endtime = time(NULL);     /* get the time of the last char inputted */
 if (iscancelled) {
     return 0;
 }
 else {
     return 1;
 }
}
/* --------------------- EVALUATE THE TYPED LESSON ------------------------*/
void evaltypedlesson(void){
register int i=0;
int numtypeerror = 0;
int numtypecorrect = 0;
int x;
double cps,cpm,wpm;
    /* if the typed lesson is not equal to */
    /* the loaded lesson,increment type errors */
    for(i=0;i<strlen(lesson);i++){
       if (typedlesson[i] != lesson[i]) {
     numtypeerror++;
       }
       else{
     numtypecorrect++;/* otherwise,increment no of correct typed chars */
       }
   }
    xtime = difftime(endtime,starttime);
    CPS = totalchartyped/ xtime;   /* compute the CPS [Character per second ] */
    CPM =  CPS*60;                /* compute the CPM [Character per minute ] */
    WPM =  CPM/5;                 /* assumed that 1 word = 5 characters */

    totalerrors = numtypeerror;    /* total characters errors typed  */
    totalcorrect = numtypecorrect; /* total correct characters typed */
    if (totalcorrect == 0 ) typeaccuracy = 0.0; /* if no correct characters typed, his accuracy is 0*/
    else typeaccuracy = (( (float)totalchartyped - (float)totalerrors) / totalchartyped) * 100;
    getch();
}
/* ------------------ DISPLAY THE TYPING SUMMARY --------------------------*/
void displaySummary(void){
  int c;
  box1(20,21,62,30,GOINGLEFT,YELLOW,10); /* container */
  box1(20,21,64,32,GOINGDOWN,BLACK,0);  /* dropshadow */
  box1(20,21,62,30,GOINGLEFT,YELLOW,0); /* container */
  drawbox(20,21,62,30,YELLOW);

  textcolor(WHITE);
  gotoxy(startx,starty+4); textcolor(LIGHTGREEN); cprintf(" .: TYPING SUMMARY :. ");
  textcolor(WHITE);
  gotoxy(startx-6,starty+5); cprintf("Accuracy                 : %.2f %    ",typeaccuracy);
  gotoxy(startx-6,starty+6); cprintf("Characters per sec.      : %.2f CPS ",CPS);
  gotoxy(startx-6,starty+7); cprintf("Characters per min.      : %.2f CPM ",CPM);
  gotoxy(startx-6,starty+8); cprintf("Words per min.           : %.2f WPM ",WPM);
  gotoxy(startx-6,starty+9); cprintf("Total correct chars type : %d ",totalcorrect);
  gotoxy(startx-6,starty+10); cprintf("Total wrong chars type   : %d ",totalerrors);
  gotoxy(startx-6,starty+11); cprintf("Total chars type         : %d  ",totalchartyped-1);

  gotoxy(40,47); textbackground(BLUE);
  textcolor(YELLOW); cprintf("Press ESC to back to Main Menu...");
  while((c = getch()) != ESC ) {} /* WAITING ESC to be pressed */
  putchar(c);
  box1(19,20,64,33,GOINGDOWN,GREEN,10); /* erase container */
  box1(5,4,76,48,GOINGRIGHT,BLUE,5);/* erase content bkcolor */
}
/* ------------ SAVED THE TYPING skills results into TEXT FILES -------------*/
void savedtypingskillsResults(void){
char str[9];

  if ((login = fopen(userprofiles,"a+")) == NULL){
   gotoxy(7,6); cprintf("error in saving user profiles %s",username);
   getch();
   exit(0);
  }

  fprintf(login,"======================== Typing Results =====================\n");
  fprintf(login,"                                                             \n");
  fprintf(login,"Date Finished             : %s\n", _strdate(str));
  fprintf(login,"Time                      : %s\n", _strtime(str));
  fprintf(login,"Lesson Name               : %s\n", lessonname);
  fprintf(login,"Accuracy                  : %.2f % \n",typeaccuracy);
  fprintf(login,"Characters per sec.       : %.2f CPS\n",CPS);
  fprintf(login,"Characters per min.       : %.2f CPM\n",CPM);
  fprintf(login,"Words per min.            : %.2f WPM\n",WPM);
  fprintf(login,"Total correct chars typed : %d \n",totalcorrect);
  fprintf(login,"Total wrong chars typed   : %d \n",totalerrors);
  fprintf(login,"Total chars typed         : %d \n",totalchartyped-1);
  fprintf(login,"                                                             \n");
  fprintf(login,"=============================================================\n");

}
/* load the user typing skills...later na lang, need more time*/
void viewtypingskillsResults(void){
int ch;

  if ((login = fopen(username,"r")) == NULL){
   gotoxy(7,6); cprintf("Cannot open a file %s",filename);
   getch();
   exit(0);
  }

gotoxy(1,1);

 /* while((ch=fgetc(login)) != EOF ){
     cprintf("%c",ch);
  }*/

  while(!feof(login)) {
     fscanf(login,"%.2f %.2f",&typeaccuracy,&WPM);
     cprintf("Acc: %.2f \n\r",typeaccuracy);
     cprintf("wpm: %.2f \n\r",WPM);
  }
  fclose(login);
}
/* ----------------  DISPLAY THE SOFTWARE DEVELOPERS -----------------------*/
void showAbout(void) {
char str[9];

   /*  hides the texts */
   textcolor(BLUE);textbackground(BLUE);
   gotoxy(30,47);cprintf("Note: Use arrow keys to move the selection....");
   gotoxy(7,47);cprintf("Today's date : %s", _strdate(str));

   box1(4,3,78,13,GOINGDOWN,BLUE,10); /* erase-header container */
   box1(24,13,60,30,GOINGDOWN,BLUE,10); /* erase - menu container */

   box1(25,13,57,35,GOINGDOWN,YELLOW,8); /* container */
   box1(25,13,59,37,GOINGDOWN,BLACK,0);  /* dropshadow */
   box1(25,13,57,35,GOINGLEFT,YELLOW,0); /* container */
   drawbox(25,13,57,35,YELLOW);

   gotoxy(startx+7,starty-5); textcolor(YELLOW);typewriter_effects(".: About :.",5);delay(100);
   textcolor(WHITE);
   gotoxy(startx+2,starty-3); typewriter_effects(" .: Typing Tutor :. ",2);delay(50);
   gotoxy(startx+2,starty-1); typewriter_effects(" Version 12.25.2004",2);delay(50);
   gotoxy(startx,starty+1); textcolor(LIGHTRED); typewriter_effects("   Copyright(c) 2005",5);delay(50);
   gotoxy(startx,starty+2);typewriter_effects(" (Year of the Chicken)",2);delay(50);
   gotoxy(startx-3,starty+4); textcolor(WHITE);typewriter_effects(" .:Jastis Legs(Pinoy version):.",2);delay(50);
   gotoxy(startx,starty+5); textcolor(LIGHTGREEN); typewriter_effects(".:arman as Lipstik-Man:. ",2);delay(50);
   gotoxy(startx,starty+6); typewriter_effects("   .:Mark as Mulawin:.",2);delay(50);
   gotoxy(startx,starty+7); typewriter_effects("  .:Eunice as KrysTala:.",2);delay(50);
   gotoxy(startx,starty+8); cprintf(" .:Yulin as Lito Cruz:.");delay(50);
   gotoxy(startx+1,starty+9); cprintf(" .:Dyncie as Bintong:. ");delay(50);
   gotoxy(startx-3,starty+10); cprintf(" .:Janus as Boboy Salongga:. ");delay(50);
   gotoxy(startx,starty+12);textcolor(YELLOW);cprintf(" \"YOU'LL BE SAFE HERE\"...");delay(50);
   gotoxy(startx-3,starty+15); typewriter_effects("igat oi! kusion tika ron beh...",10);delay(50);
   getch();
   //exit(0);
   box1(24,12,60,40,GOINGDOWN,BLUE,5); /* container */
}

/* ---------------------------DRAW BOX---------------------------------*/
void drawbox(int left,int top,int right,int bottom,int color){
register int ctr,ctr2;
char topLeftChar    = 'Ú';
char topRightChar   = '¿';
char bottomLeftChar = 'À';
char bottomRightChar= 'Ù';
char horizontalChar = 'Ä';
char verticalChar   = '³';

 textcolor(color);
 gotoxy(left,top);putch(topLeftChar);
 gotoxy(right,top);putch(topRightChar);
 gotoxy(left,bottom);putch(bottomLeftChar);
 gotoxy(right,bottom);putch(bottomRightChar);

 for(ctr=left+1;ctr < right;ctr++){
    gotoxy(ctr,top);putch(horizontalChar);
    gotoxy(ctr,bottom);putch(horizontalChar);
 }

 for(ctr=top+1;ctr<bottom;ctr++){
    gotoxy(left,ctr);putch(verticalChar);
    gotoxy(right,ctr);putch(verticalChar);
 }

}

void box1(int left,int top,int right,int bottom,int opendirection,int shadecolor,int mydelay){
register int i;
register int ctr,ctr2;
 textbackground(shadecolor);
 switch(opendirection){
   case GOINGDOWN: /* open downward */
     for(ctr=top+1;ctr < bottom;ctr++) {
        for(ctr2=left+1;ctr2<right;ctr2++){
        gotoxy(ctr2,ctr); cprintf(" ");
        }
     delay(mydelay);
     }
     break;
   case GOINGLEFT: /* open to left*/
    for(ctr=left+1;ctr < right;ctr++){
        for(ctr2=top+1;ctr2<bottom;ctr2++){
     gotoxy(ctr,ctr2);cprintf(" ");
        }
    delay(mydelay);
    }
    break;
   case GOINGRIGHT:
   for(ctr=right+1;ctr > left;ctr--){
      for(ctr2=top+1;ctr2<bottom;ctr2++){
         gotoxy(ctr,ctr2);cprintf(" ");
      }
   delay(mydelay);
   }

  }
}