#include <iostream>
#include<GL/glut.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define size 6
static int stack[10],top=-1,count=0,elem=0,a,l,flag=0,flag2=0;
static int x = 125,y = 125,x1=200,y1=150,x0=125,y0=125,x2= 400,y2= 125;          
static char buf[100],text[100];

void renderbitmap(float x,float y,void *font,char *string){
	char *c;
	glRasterPos2f(x,y);
	for(c=string;*c!='\0';c++){
		glutBitmapCharacter(font,*c);
 	}
}
 
int isempty(){
   if(top == -1)
      return 1;
   else
      return 0;
}

int isfull(){
   if(top == size)
      return 1;
   else
      return 0;
}

int peek(){
   return stack[top];
}

int pop(){
	int data;
	if(!isempty()) {
		data = stack[top];
        printf("poped element is : %d\n\n",data);
        top = top - 1;  
	    count--; 
        return data;
    } 
}

int push(int data){
   if(!isfull()) {
      top = top + 1;   
      stack[top] = data;
      count++;
    } 
}

void draw_outline(){
	glColor3f(1,0,0);
	glBegin(GL_LINE_LOOP);
	glVertex2i(100,100);
	glVertex2i(100,500);
	glVertex2i(200,500);
	glVertex2i(200,100);
	glEnd();
	glFlush();
}

void draw_cell(){
	glColor3f(1,0,0);
	glBegin(GL_LINE_LOOP);
	glVertex2i(x,y);
	glVertex2i(x,y+50);
	glVertex2i(x+50,y+50);
	glVertex2i(x+50,y);
   	glEnd();
	glFlush();
}

void draw_previous(){
	int i;
	if(y0 != y1){
		for(i=y0;i<y1;i+=50){
			glBegin(GL_LINE_LOOP);
			glVertex2i(x0,i);
			glVertex2i(x,i+50);
			glVertex2i(x+50,i+50);
			glVertex2i(x+50,i);
   			glEnd();
			glFlush();
		}
	}
}

void draw_pointer(){
	glBegin(GL_LINE_LOOP);
	glVertex2i(x1+10,y1+10);
	glVertex2i(x1,y1);
	glVertex2i(x1+10,y1-10);
	glEnd();
	glBegin(GL_LINES);
	glVertex2i(x1+10,y1);
	glVertex2i(x1+40,y1);
	glEnd();
	glFlush();
}

void display(){
	int i=0;
	glClear(GL_COLOR_BUFFER_BIT);
	draw_outline();
	int temp_x=x,temp_y = y;
	for(i=0;i<=top;i++){
		glPushMatrix();
		glTranslated(0,50*i,0);
    	draw_cell();
    	//makedelay(1);
    	sprintf(buf," %d",stack[i]);
		renderbitmap(x+10,y+15,GLUT_BITMAP_TIMES_ROMAN_24,buf);
		glFlush();
		if(i==top)
		{
			draw_pointer();
			sprintf(buf,"TOP");
			renderbitmap(x1+45,y1 -5,GLUT_BITMAP_TIMES_ROMAN_24,buf);
		}
		glPopMatrix();
    }
    sprintf(buf,"STACK OPERATIONS");
	renderbitmap(150,550,GLUT_BITMAP_TIMES_ROMAN_24,buf);
	sprintf(buf,"STATUS :%s  ",text);
	renderbitmap(300,400,GLUT_BITMAP_TIMES_ROMAN_24,buf);
	if(flag == 1){
		sprintf(buf," %d",a);
		renderbitmap(508,400,GLUT_BITMAP_TIMES_ROMAN_24,buf);
	}
	if(flag2==1){
		sprintf(buf," %d",stack[top]);
		renderbitmap(508,400,GLUT_BITMAP_TIMES_ROMAN_24,buf);
	}
	glFlush();
}

void Select(int ch){
	flag=0;
	flag2=0;
	switch(ch){
		case 1:if(!isfull()){
			   printf("enter a number to be pushed to stack :");
			   scanf("%d",&elem);
			   push(elem);
			   printf("\n\n");
			   glFlush();
			   draw_cell();
			   sprintf(buf," %d",elem);
	           renderbitmap(x+10,y+15,GLUT_BITMAP_TIMES_ROMAN_24,buf);
			   strcpy(text," PUSHED ");
			   flag2=1;
			   glFlush();
			   glutPostRedisplay();
  			   }
			   else{
			   		printf("Could not insert data, Stack is full\n\n");
			   		sprintf(buf,"STACK IS FULL");
			        renderbitmap(300,370,GLUT_BITMAP_TIMES_ROMAN_24,buf);
			        glFlush();
			    }
			   break;
		case 2:int k;
			    if(!isempty()){
			    a =pop();
			    strcpy(text," POPPED ");
			    flag=1;
			    glFlush();
			    glutPostRedisplay();
				}
			    else{
					printf("Could not retrieve data, Stack is empty\n\n");
					sprintf(buf,"STACK IS EMPTY");
			        renderbitmap(300,370,GLUT_BITMAP_TIMES_ROMAN_24,buf);	
			        glFlush();
				}

				break;		
		case 3:if(!isempty()){
			   l = peek();
			   printf("top of stack is : %d\n\n",l);
			   sprintf(buf,"TOP OF STACK IS : %d",l);
			   renderbitmap(300,350,GLUT_BITMAP_TIMES_ROMAN_24,buf);
			   glFlush();
		       }
		       else {
			   		sprintf(buf,"STACK IS EMPTY");
			        renderbitmap(300,370,GLUT_BITMAP_TIMES_ROMAN_24,buf);
		       		printf("Could not retrieve data, Stack is empty\n\n");
		       		glFlush();
		       	}

		       	break;	  
	}
}

void init(){
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0,600,0,600);
	glMatrixMode(GL_MODELVIEW);
}


/*void introscreen()
 {
	glColor3f(1.f,1.f,1.f);
	char buf[100]={0};
	sprintf(buf," BNM INSTITUTE OF TECHNOLOGY");
	renderbitmap(170,400,GLUT_BITMAP_TIMES_ROMAN_24,buf);
	glColor3f(1.f,1.f,1.f);
	sprintf(buf,"PROJECT NAME : STACK OPERATIONS");
	renderbitmap(170,300,GLUT_BITMAP_TIMES_ROMAN_24,buf);
	glColor3f(1.f,1.f,1.f);
	sprintf(buf,"NAME : BHASKAR S");
	renderbitmap(170,250,GLUT_BITMAP_TIMES_ROMAN_24,buf);
	glColor3f(1.f,1.f,1.f);
	sprintf(buf,"USN : 1BG15CS024");
	renderbitmap(170,230,GLUT_BITMAP_TIMES_ROMAN_24,buf);
	glColor3f(1.f,1.f,1.f);
	sprintf(buf,"CSE A2");
	renderbitmap(170,210,GLUT_BITMAP_TIMES_ROMAN_24,buf);
}

void mydisplay(void)
{
 glClear(GL_COLOR_BUFFER_BIT);
 if(flag==0)
introscreen();
 if(flag==1)
  display(); 
}


void keyboard( unsigned char key, int x, int y ){
	switch(key){
		case 13:if(flag==0) //Ascii of 'enter' key is 13
    			flag=1;
  				break;
    }
    mydisplay();
}*/


int main(int argc, char **argv){
	static int z;
	printf("enter a number as stack is empty :");
	scanf("%d",&z);
	printf("\n\n");
	push(z);
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(600,600);
	glutCreateWindow("STACK OPERATIONS");
	init();
	glutDisplayFunc(display);
//	glutKeyboardFunc(keyboard);
	glutCreateMenu(Select);
	glutAddMenuEntry("PUSH",1);
	glutAddMenuEntry("POP",2);
	glutAddMenuEntry("PEEK",3);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
//	glutTimerFunc(40,makedelay,1);
	glutMainLoop();
	return 0;
}
