#include<conio.h>
#include<iostream.h>
#include<stdio.h>
#include<stdlib.h>

int flag=0,t,k,x=0;
char c;
int far*SCR=(int far*)0XB8000000;

char A[9][8]={{1,2,3,4,5,6,7,8},
	      {1,2,3,4,5,6,7,8},
	      {1,2,3,4,5,6,7,8},
	      {1,2,3,4,5,6,7,8},
	      {1,2,3,4,5,6,7,8},
	      {1,2,3,4,5,6,7,8},
	      {1,2,3,4,5,6,7,8},
	      {1,2,3,4,5,6,7,8},
	      {1,2,3,4,5,6,7,8}};


struct stack{

	char s[1000];
	int last;

	void init(void) {
	      last=-1;

	      }
	int ISEMPTY(){
		return last == -1;
	}
	int ISFULL(){
		return last==999;
	}
	void push(char c){
		if(!ISFULL() && c!=NULL){
			last++;
			s[last]=c;
		}
	}
	char pop(){
		if(!ISEMPTY())
			return s[last--];
		else
			return 0;
	}

}; stack p,q;


void f1(){	if (!p.ISFULL())
						//char
			if(flag==0){
			 p.push(c);
			 x=x+1;
			 }
			 else{
			       if(!q.ISEMPTY()){
					p.pop();
					p.push(c);
					p.push(q.pop());
					x=x+1;
					}
			       else{
				    p.push(c);
				    x=x+1;
				    }

			 }

}

void f2(){ 	 flag=!flag ;		 	//ins

	 }

void f3(){                	      		//left
		if (!p.ISEMPTY())
			 q.push(p.pop());
			 x=x-1;
	 }

void f4(){                             		//right
		if (!q.ISEMPTY())
			p.push(q.pop());
			else
			{c=32; p.push(c);}
			x=x+1 ;
		}

void f5(){                              	//del
		if (!q.ISEMPTY())
			 q.pop();
	 }

void f6(){                              	//back space
		if (!p.ISEMPTY())
			p.pop();
			x=x-1;
	 }

void f7(){					//home

		x=0;
		while (!p.ISEMPTY())
			 q.push(p.pop());

	 }

void f8(){

		while (!q.ISEMPTY())            //end
			p.push(q.pop());

	 }



int FUNCKEY (char &c)
{
	c = getch();
	if (c==0){
		   c=getch();
		   return 0;

		  }
	else
		   return 1 ;
}

void getevent(){
	if (t==0){
	if (c=='R')		k=1;   //ins
	else if (c=='K')       	k=2;
	else if (c=='M')	k=3;
	else if (c=='G')	k=6;     //home
	else if (c=='O')	k=7;     //end
	else if (c=='S')	k=4;     //delete

	}
	else{
	if ((c>47&&c<58) || (c>64&&c<91) || (c>96 && c<123) || c==32)      k=0 ;  //char
	else if (c==8)		k=5;     //back



	}
}

void init(){


	for(int m=16;m<60;m++)
	SCR[12*80+m]=113*256;



}

void f0(){
	     for (int w=0;w<1000;w++){

			p.s[w]=NULL;
			q.s[w]=NULL;
		}
}


void(*func[9])(void)={f0,f1,f2,f3,f4,f5,f6,f7,f8};

void show(){

	 //show p
	 if(x>=0){
		int a=0;
		int b=p.last-x+1 ;
		while(b!=p.last+1||a!=x){
			SCR[12*80+17+a]=112*256+p.s[b];
			a=a+1;
			b=b+1;
			}
	      }

	//show curdor
	if(x>=0&&x<42){
			if(flag==0)	SCR[13*80+x+16]=15*256+'^';
			else            SCR[13*80+x+16]=135*256+'^';
			}

	else if(x>41) {
			x=42;
			if(flag==0)
			SCR[13*80+x+16]=15*256+'^';
			else
			SCR[13*80+x+16]=135*256+'^';
		       }
	else if(x<0) {
			x=0;
			if(flag==0)
			SCR[13*80+x+16]=15*256+'^';
			else
			SCR[13*80+x+16]=135*256+'^';
		      }


	 //show q
	 if(x>-1){
		int c=q.last;
		int d=x ;
		while((c!=-1||(d-1)!=x+q.last)){
			if(d+17<60)
			SCR[12*80+d+17]=112*256+q.s[c];
			c=c-1;
			d=d+1;
			}
		}
}

void main(void){

	  q.init();
	  p.init();
		int cs=0;
		clrscr();
		SCR[13*80+16]=15*256+'^';
		init();
	t=FUNCKEY (c);
	(*func[cs])();
	while( t!=1 || c!=27 ){

		clrscr();
		init();
		getevent();
		cs=A[cs][k];
		(*func[cs])();
		show();
		t=FUNCKEY(c);
	}


}