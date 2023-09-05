#include<dos.h>
#include<fstream.h>
#include<math.h>
#include<iomanip.h>
#include<stdlib.h>
#include<conio.h>
#include<stdio.h>
#include<string.h>
#include<process.h>
int nomatch=0;
struct Passenger                               //For Passenger details
{
	char name[50], coach[5], berth[3], gender;
	int age, seat;
};
struct train                                 //Shows train no. by checking Train No
{
	unsigned int tno;
	int avgspd;
	char tname[50],zone[50],llink[50],sou[50],dest[50],rake[10];
	train()
	{
		strcpy(tname," ");
	}
	int rtntno()
	{
		return tno;
	}
	void displaytrain()
	{
		puts(tname);
	}
	void display()
	{
		gotoxy(33,5);
		cout<<"TRAIN DETAILS ARE...\n";
		gotoxy(15,7);
		cout<<"Train Number:	       "<<tno<<endl;
		gotoxy(15,9);
		cout<<"Train Name:              ";puts(tname);
		gotoxy(15,11);
		cout<<"Source Station:          ";puts(sou);
		gotoxy(15,13);
		cout<<"Destination Station:     ";puts(dest);
		gotoxy(15,15);
		cout<<"Average Speed:           "<<avgspd<<endl;
		gotoxy(15,17);
		cout<<"Rake Type:               ";puts(rake);
		gotoxy(15,19);
		cout<<"Loco Links:              ";puts(llink);
		gotoxy(15,21);
		cout<<"Operating Zone:          ";puts(zone);
	}
};
struct IR                                      //Structure for PRS
{
	unsigned int tno;
	Passenger pass[5];
	char cls[5], date[15], from[50], to[50], quota[25];
	int amount, km, pnr, nop, avbl, wl;
	void calc_amount()                     //Calculates the total fare
	{
		if(strcmpi(cls,"SL")==0 || strcmpi(cls,"2S")==0)
			amount=nop*(km*0.499);
		else if(strcmpi(cls,"3AC")==0)
			amount=nop*(km*1.367);
		else if(strcmpi(cls,"2AC")==0)
			amount=nop*(km*1.9705);
		else if(strcmpi(cls,"1AC")==0)
			amount=nop*(km*4.2);
		else if(strcmpi(cls,"CC")==0)
			amount=nop*(km*1.7461);
	}
	void ttlavbl()                             //Sets availability for
	{                                          //each class
		if(strcmpi(cls,"SL")==0)
			avbl=72;
		else if(strcmpi(cls,"3AC")==0)
			avbl=64;
		else if(strcmpi(cls,"2AC")==0)
			avbl=48;
		else if(strcmpi(cls,"CC")==0)
			avbl=73;
		else if(strcmpi(cls,"1AC")==0)
			avbl=28;
		else if(strcmpi(cls,"2S")==0)
			avbl=108;
	}
	void blanktkt();
	void berthallot(int i);
};
void IR::blanktkt()                        	  //prints the ticket layout
{
	int i;
	clrscr();
	for(i=4;i<=23;i++)
	{
		gotoxy(1,i);
		cout<<"³   ³";
		gotoxy(76,i);
		cout<<"³   ³";
		if(i%2==0)
		{
			gotoxy(3,i);
			cout<<"o";
			gotoxy(78,i);
			cout<<"o";
		}
		if(i<=21)
		{
			gotoxy(66,i);
			cout<<"³";
		}
		if(i>=6 && i<=7)
		{
			gotoxy(53,i);
			cout<<"³";
		}
		if(i>=4 && i<10)
		{
			gotoxy(21,i);
			cout<<"³";
		}
	}
	for (i=1;i<=80;i++)
	{
		gotoxy(i,3);
		cout<<"_";
		gotoxy(i,24);
		cout<<"-";
		if(i>=6 && i<=65)
		{
			gotoxy(i,14);
			cout<<"-";
			gotoxy(i,16);
			cout<<"-";
			if(i>=22)
			{
				gotoxy(i,5);
				cout<<"-";
				gotoxy(i,8);
				cout<<"-";
			}
			if(i>20)
			{
				gotoxy(i,10);
				cout<<"-";
			}
		}
		if(i>=6 && i<=66)
		{
			gotoxy(i,22);
			cout<<"-";
			if(i<=15)
			{
				gotoxy(i,12);
				cout<<"-";
			}
			if(i<=20)
			{
				gotoxy(i,6);
				cout<<"-";
				gotoxy(i,8);
				cout<<"-";
				gotoxy(i,10);
				cout<<"-";
			}
		}
	}
	gotoxy(67,8);
	cout<<" WELCOME";
	gotoxy(67,10);
	cout<<"   TO   ";
	gotoxy(67,12);
	cout<<"JHARKHAND";
	gotoxy(67,15);
	cout<<"THE  LAND";
	gotoxy(67,17);
	cout<<"   OF";
	gotoxy(67,19);
	cout<<" NATURAL";
	gotoxy(67,21);
	cout<<" BEAUTY";
	gotoxy(11,7);
	cout<<"P.N.R";
	gotoxy(78,1);
	cout<<"@KA";
	gotoxy(6,5);
	cout<<"SWACHCHH BHARAT";
	gotoxy(7,11);
	cout<<"  CLASS\t\t";
	cout<<"  Journey Cum Reservation Ticket";
	gotoxy(16,11);
	cout<<"³";
	gotoxy(34,4);
	cout<<"H A P P Y  J O U R N E Y";
	gotoxy(56,6);
	cout<<"TICKET NO.";
	gotoxy(56,7);
	cout<<"/03268467";
	gotoxy(55,9);
	cout<<"³ PRS-CSTM";
	gotoxy(25,7);
	cout<<"TRAIN NO.     DATE      KM";
	gotoxy(7,15);
	cout<<"COACH  SEAT  GENDER  AGE	      SF CHARGE       T.CASH";
	gotoxy(15,23);
	cout<<"J  H  A  R  K  H  A  N  D   T  O  U  R  I  S  M";
}
void coach_allot(int j, IR &i)                            //Allots coach to each pass.
{
	int seat=i.avbl+1;
	if(seat<=0)
		i.wl=seat;
	if(i.pass[j].seat==0)
	{
		i.avbl--;
		i.pass[j].seat--;
	}
	if(strcmpi(i.cls,"SL")==0)
	{
		if(seat<=0 && seat>-63)
			strcpy(i.pass[j].coach,"RAC");
		else if(seat<=-63)
		{
			i.wl+=62;
			strcpy(i.pass[j].coach,"WL");
		}
		else if(seat>0)
			strcpy(i.pass[j].coach,"S5");
	}
	else if(strcmpi(i.cls,"3AC")==0)
	{
		if(seat<=0 && seat>-39)
			strcpy(i.pass[j].coach,"RAC");
		else if(seat<=-39)
		{
			i.wl+=38;
			strcpy(i.pass[j].coach,"WL");
		}
		else if(seat>0)
			strcpy(i.pass[j].coach,"B2");
	}
	else if(strcmpi(i.cls,"2AC")==0)
	{
		if(seat<=0 && seat>=-20)
			strcpy(i.pass[j].coach,"RAC");
		else if(seat<-20)
		{
			i.wl+=19;
			strcpy(i.pass[j].coach,"WL");
		}
		else if(seat>0)
			strcpy(i.pass[j].coach,"A1");
	}
	else if(strcmpi(i.cls,"1AC")==0)
	{
		if(seat<=0)
			strcpy(i.pass[j].coach,"WL");
		else
			strcpy(i.pass[j].coach,"CNF");
	}
	else if(strcmpi(i.cls,"CC")==0)
	{
		if(seat<=0 && seat>-41)
			strcpy(i.pass[j].coach,"RAC");
		else if(seat<=-41)
		{
			i.wl+=40;
			strcpy(i.pass[j].coach,"WL");
		}
		else if(seat>0)
			strcpy(i.pass[j].coach,"C2");
	}
	else if(strcmpi(i.cls,"2S")==0)
	{
		if(seat<=0 && seat>-100)
			strcpy(i.pass[j].coach,"RAC");
		else if(seat<=-100)
		{
			i.wl+=99;
			strcpy(i.pass[j].coach,"WL");
		}
		else if(seat>0)
			strcpy(i.pass[j].coach,"D5");
	}
	if(strcmpi(i.pass[j].coach,"WL")==0)
		i.pass[j].seat=abs(i.wl);
}
void IR::berthallot(int i)       		//Allots berth to each passenger
{
	if(strcmpi(cls,"SL")==0)
	{
		if(pass[i].seat==23||pass[i].seat==39||pass[i].seat==47||pass[i].seat==71)
		{
			pass[i].seat-=1;
			avbl-=1;
		}
		if(pass[i].seat%8==1||pass[i].seat%8==4)
			strcpy(pass[i].berth,"LB");
		else if(pass[i].seat%8==2||pass[i].seat%8==5)
			strcpy(pass[i].berth,"MB");
		else if(pass[i].seat%8==3||pass[i].seat%8==6)
			strcpy(pass[i].berth,"UB");
		else if(pass[i].seat%8==0)
			strcpy(pass[i].berth,"SU");
		else if(pass[i].seat==7||pass[i].seat==15||pass[i].seat==55||pass[i].seat==63)
			strcpy(pass[i].berth,"SL");
	}
	else if(strcmpi(cls,"3AC")==0)
	{
		if(pass[i].seat==23||pass[i].seat==31||pass[i].seat==39||pass[i].seat==47)
		{
			pass[i].seat-=1;
			avbl-=1;
		}
		if(pass[i].seat%8==1||pass[i].seat%8==4)
			strcpy(pass[i].berth,"LB");
		else if(pass[i].seat%8==2||pass[i].seat%8==5)
			strcpy(pass[i].berth,"MB");
		else if(pass[i].seat%8==3||pass[i].seat%8==6)
			strcpy(pass[i].berth,"UB");
		else if(pass[i].seat%8==0)
			strcpy(pass[i].berth,"SU");
		else if(pass[i].seat==7||pass[i].seat==15||pass[i].seat==63)
			strcpy(pass[i].berth,"SL");
	}
	else if(strcmpi(cls,"2AC")==0)
	{
		if(pass[i].seat==11||pass[i].seat==23||pass[i].seat==29||pass[i].seat==35||pass[i].seat==47)
		{
			pass[i].seat-=1;
			avbl-=1;
		}
		if(pass[i].seat%6==1||pass[i].seat%6==3)
			strcpy(pass[i].berth,"LB");
		else if(pass[i].seat%6==2||pass[i].seat%6==4)
			strcpy(pass[i].berth,"UB");
		else if(pass[i].seat%6==0)
			strcpy(pass[i].berth,"SU");
		else if(pass[i].seat==5||pass[i].seat==17||pass[i].seat==41)
			strcpy(pass[i].berth,"SL");
	}
	else if(strcmpi(cls,"CC")==0)
	{
		if(pass[i].seat%10==5||pass[i].seat%10==9||pass[i].seat%10==0||pass[i].seat%10==4||pass[i].seat==1||pass[i].seat==4||pass[i].seat==73)
			strcpy(pass[i].berth,"W");
		else if(pass[i].seat%10==6||pass[i].seat%10==1)
			strcpy(pass[i].berth,"M");
		else if(pass[i].seat%10==3||pass[i].seat%10==8||pass[i].seat%10==7||pass[i].seat%10==2)
			strcpy(pass[i].berth,"A");
	}
	else if(strcmpi(cls,"2S")==0)
	{
		if(pass[i].seat%12==1||pass[i].seat%12==6||pass[i].seat%12==7||pass[i].seat%12==0)
			strcpy(pass[i].berth,"W");
		else if(pass[i].seat%12==2||pass[i].seat%12==5||pass[i].seat%12==8||pass[i].seat%12==11)
			strcpy(pass[i].berth,"M");
		else if(pass[i].seat%12==3||pass[i].seat%12==9||pass[i].seat%12==10||pass[i].seat%12==4)
			strcpy(pass[i].berth,"A");
	}
	else if(strcmpi(cls,"1AC")==0)
		strcpy(pass[i].berth," ");
}
int calc_cq(IR &i)
{
	int cqcharge=0;
	if(strcmpi(i.cls,"SL")==0)
		cqcharge=100;
	else if(strcmpi(i.cls,"3AC")==0)
		cqcharge=250;
	else if(strcmpi(i.cls,"2AC")==0)
		cqcharge=300;
	else if(strcmpi(i.cls,"CC")==0)
		cqcharge=100;
	else if(strcmpi(i.cls,"1AC")==0 || strcmpi(i.cls,"FC")==0)
		cqcharge=350;
	else if(strcmpi(i.cls,"2S")==0)
		cqcharge=10;
	return cqcharge;
}
void quota(int k, IR &i)                      //Alters the fare as per the quota
{
	if(strcmpi(i.quota,"Senior Citizen")==0)
	{
		int old=0, amt, j;
		for(j=0;j<i.nop;j++)
			if(i.pass[j].age>=60)
				old++;           //checks total senior citizen in each entry
		amt=i.amount/i.nop;
		amt*=old;
		if(strcmpi(i.cls,"2S")==0 ||strcmpi(i.cls,"SL")==0)
			amt/=2;
		else if(strcmpi(i.cls,"3AC")==0 ||strcmpi(i.cls,"2AC")==0||strcmpi(i.cls,"1AC")==0 ||strcmpi(i.cls,"CC")==0)
			amt-=(amt*0.75);
		i.amount-=amt;
	}
	else if(strcmpi(i.quota,"Tatkal")==0)
		i.amount+=(i.nop*calc_cq(i));
	else if(strcmpi(i.quota,"Ladies")==0 && strcmpi(i.cls,"SL")==0 && i.nop==1)
		if(i.pass[0].age>=40 && i.pass[0].gender=='F')
		{
			strcpy(i.pass[0].coach,"S4");
			i.pass[0].seat=12;
			strcpy(i.pass[0].berth,"LB");
		}
	else if(strcmpi(i.quota,"Disabled")==0)
		i.amount-=(i.amount*0.50);
	else if(strcmpi(i.quota,"Defence")==0)
		i.amount-=(i.amount*0.30);
	else if(strcmpi(i.quota,"Foreign Tourist")==0)
		i.amount+=(i.amount*0.10);
	else if(strcmpi(i.quota,"General")==0)
		i.amount=(1*i.amount);
	else if(strcmpi(i.quota,"Premium Tatkal")==0)
	{       randomize();
		int dfare=random(500-100+1)+100;
		i.amount+=(i.nop*dfare);
	}
	else
	{
		gotoxy(17,k+1);
		cout<<"Not Eligible for Quota or Quota Not Available.";
		nomatch++;
	}
}
void altercoach(IR &i)
{
	for(int j=0;j<i.nop;j++)
		if(strcmpi(i.pass[j].coach,"RAC")==0 || strcmpi(i.pass[j].coach,"WL")==0)
		{
			strcpy(i.pass[j].berth," ");
		}
}
void processing()    				//Displays processing screen
{
	randomize();
	int prtdot=1, late=random(10-3+1)+1;
	for(int i=0;i<=late;i++)
	{
		clrscr();
		gotoxy(33,13);
		cout<<"Processing";
		if(prtdot==1)
			cout<<".";
		else if(prtdot==2)
			cout<<"..";
		else if(prtdot==3)
			cout<<"...";
		else if(prtdot==4)
			cout<<"....";
		prtdot++;
		if(prtdot>4)
			prtdot=1;
		delay(300);
	}
}
void border()                           //Makes border around the Screen
{
	for (int i=2;i<=79;i++)
	{
		gotoxy(i,1);
		cout<<"²";
		gotoxy(i,25);
		cout<<"²";
		delay(10);
	}
	for(i=1;i<=24;i++)
	{
		gotoxy(2,i);
		cout<<"²²";
		gotoxy(78,i);
		cout<<"²²";
		delay(10);
	}
	gotoxy(34,1);
	cout<<"INDIAN RAILWAYS";
}
void border2()                           //Makes border around the Screen
{
	for (int i=14;i<=66;i++)
	{
		gotoxy(i,5);
		cout<<"±";
		gotoxy(i,22);
		cout<<"±";
		delay(10);
	}
	for(i=5;i<=22;i++)
	{
		gotoxy(14,i);
		cout<<"±±";
		gotoxy(66,i);
		cout<<"±±";
		delay(10);
	}
}
void menu();
void helpmenu();
void newtkt()                          			//Books a new ticket
{
	IR i,c;
	int pnrcpy;
	clrscr();
	border();
	fstream f,t;
	train trn;
	f.open("PRS.DAT",ios::in | ios::binary);
	t.open("TRAIN.DAT", ios::in | ios::binary);
	randomize();
	b:                                        //Randomly generates a PNR
	pnrcpy=random(5991-1231+1)+1231;
	while(f.read((char*)&i, sizeof(i)))       //Loop checks that the
		if(pnrcpy==i.pnr)                 //randomly selected no. is
			goto b;                   //already used or not
	i.pnr=pnrcpy;
	int k=10;
	gotoxy(10,3);
	cout<<"Enter Train No.		: ";
	cin>>i.tno;
	while(t.read((char*)&trn,sizeof(trn)))
		if(i.tno==trn.rtntno())
		{
			gotoxy(50,3);
			trn.displaytrain();
		}
	gotoxy(10,4);
	cout<<"No. of Pass. (Max. 4)		: ";
	cin>>i.nop;
	gotoxy(10,5);
	cout<<"Date of Journey(DD-MM-YY)	: ";
	cin>>i.date;
	gotoxy(10,6);
	cout<<"Class				: ";
	cin>>i.cls;
	gotoxy(10,7);
	cout<<"Originating Station            : ";
	gets(i.from);
	gotoxy(10,8);
	cout<<"Destination Station            : ";
	gets(i.to);
	gotoxy(10,9);
	cout<<"KMS				: ";
	cin>>i.km;
	i.calc_amount();
	f.close();
	f.open("PRS.DAT", ios::in | ios::binary);
	i.ttlavbl();
	int nopiec=0,seat=i.avbl;
	while(f.read((char*)&c, sizeof(c)))
	{
		if((strcmpi(c.cls,i.cls)==0) && (c.tno==i.tno) && (strcmpi(c.quota,i.quota)==0) && (strcmpi(c.date,i.date)==0))
			for(int k=0;k<c.nop;k++)
			{
				nopiec+=1;
				i.avbl=i.pass[k].seat-1;
			}
	}
	if(nopiec>0)
		nopiec++;
	if(i.avbl==(seat-nopiec))
		i.avbl-=nopiec;
	f.close();
	for(int j=0;j<i.nop;j++)
	{
		gotoxy(10,k);
		cout<<"Name of Passenger "<<j+1<<"		: ";
		gets(i.pass[j].name);
		k++;
		gotoxy(10,k);
		cout<<"Gender(M/F)		        : ";
		cin>>i.pass[j].gender;
		k++;
		gotoxy(10,k);
		cout<<"Age				: ";
		cin>>i.pass[j].age;
		k++;
		if(i.avbl==0)
			i.avbl--;
		if(i.avbl>0)
		{
			i.pass[j].seat=i.avbl;
			i.avbl--;
		}
		else
		{
			i.pass[j].seat=abs(i.avbl);
			i.avbl--;
		}
		i.berthallot(j);
		coach_allot(j,i);

	}
	gotoxy(10,k);
	cout<<"Quota                          : ";
	gets(i.quota);
	quota(k+1,i);
	if(i.tno/1000==12 || i.tno/1000==22 || i.tno/1000==20)     //Adds SF charge for SF train
		i.amount+=20;
	if(nomatch==0)
	{
		gotoxy(10,24);
		altercoach(i);
		cout<<"Booking Success;\tYour PNR: 887860"<<i.pnr<<"     Fare: "<<i.amount<<endl;
		f.open("PRS.DAT", ios::app | ios::binary);     //Writes data in file
		f.write((char*)&i, sizeof(i));
	}
	else
	{
		gotoxy(30,24);
		cout<<"Exiting to Main Menu";
		delay(2000);
		menu();
	}
	getch();
}
void showalltkt()                         //Shows all tickets in Binary File
{
	int j = 5,check=0;
	IR i;
	fstream f;
	f.open("PRS.DAT",ios::in |ios::binary);
	clrscr();
	border();
	gotoxy(6,3);
	cout<<"T.NO.";
	gotoxy(14,3);
	cout<<"NO. OF PASS";
	gotoxy(29,3);
	cout<<"DATE";
	gotoxy(39,3);
	cout<<"FROM";
	gotoxy(55,3);
	cout<<"TO";
	gotoxy(70,3);
	cout<<"PNR";
	for(int x = 4;x<=77;x++)
	{
		gotoxy(x,4);
		cout<<"-";
	}
	while(f.read((char*)&i,sizeof(i)))
	{
		check=1;
		gotoxy(5,j);
		cout<<i.tno;
		gotoxy(19,j);
		cout<<i.nop;
		gotoxy(27,j);
		cout<<i.date;
		gotoxy(39,j);
		puts(i.from);
		gotoxy(53,j);
		puts(i.to);
		gotoxy(67,j);
		cout<<"887860"<<i.pnr;
		j++;
		if(j==20)              //Resets printing to top when screen is full
		{
			gotoxy(24,22);
			cout<<"Press Enter to view Next Page...";
			getch();
			j=5;
			clrscr();
			border();
			gotoxy(6,3);
			cout<<"T.NO.";
			gotoxy(14,3);
			cout<<"NO. OF PASS";
			gotoxy(29,3);
			cout<<"DATE";
			gotoxy(39,3);
			cout<<"FROM";
			gotoxy(55,3);
			cout<<"TO";
			gotoxy(70,3);
			cout<<"PNR";
			for(x = 4;x<=77;x++)
			{
				gotoxy(x,4);
				cout<<"-";
			}
		}
		delay(200);
	}
	if(check==0)
	{
		gotoxy(28,13);
		cout<<"NO TICKET RECORD IN DATABASE";
	}
	getch();
}
void displaytkt(IR i)                      //Displays all data at a
{                                          //particular place
	clrscr();
	i.blanktkt();
	train trn;
	fstream t;
	t.open("TRAIN.DAT", ios::in | ios::binary);
	delay(200);
	gotoxy(9,9);
	cout<<"887860"<<i.pnr;
	delay(200);
	gotoxy(26,9);
	cout<<i.tno<<"      "<<i.date<<"   "<<i.km;
	delay(200);
	gotoxy(10,13);
	cout<<i.cls;
	delay(200);
	gotoxy(22,13);
	puts(i.from);
	delay(200);
	gotoxy(40,13);
	puts(i.to);
	if(strcmpi(i.cls,"1AC")==0 && i.avbl>0)     //shows pass. details for 1AC
	{
		for(int j=0;j<i.nop;j++)
		{
			delay(200);
			gotoxy(9,17+j);
			cout<<i.pass[j].coach;
			gotoxy(14,17+j);
			cout<<i.pass[j].gender;
			gotoxy(17,17+j);
			cout<<i.pass[j].age;
			gotoxy(21,17+j);
			cout<<"PNR 887860"<<i.pnr;
		}
	}
	else
	{
		for(int j=0;j<i.nop;j++)
		{
			delay(200);
			gotoxy(9,17+j);
			cout<<i.pass[j].coach;
			gotoxy(14,17+j);
			cout<<i.pass[j].seat;
			gotoxy(18,17+j);
			cout<<i.pass[j].berth;
			gotoxy(24,17+j);
			cout<<i.pass[j].gender;
			gotoxy(29,17+j);
			cout<<i.pass[j].age;
		}
	}
	gotoxy(40,17);
	if(i.tno/1000==12 || i.tno/1000==22 || i.tno/1000==20)  //Checks whether the train
	{                                                       //is SF or not
		delay(200);
		cout<<"20.00";
	}
	delay(200);
	gotoxy(55,17);
	cout<<i.amount;
	delay(200);
	while(t.read((char*)&trn,sizeof(trn)))  //prints train name when train no. matches in file
		if(i.tno==trn.rtntno())
		{
			gotoxy(35,21);
			trn.displaytrain();
		}
	getch();
}
void searchbypnr()                        //Searches for the ticket with PNR
{                                         //entered by the user
	int pnrcpy;
	clrscr();
	IR i;
	int found=0;
	border();
	gotoxy(20,13);
	cout<<"Enter Last 4 Digits of PNR	:887860";
	cin>>pnrcpy;
	fstream f;
	f.open("PRS.DAT", ios::in | ios:: binary);
	while(f.read((char*)&i, sizeof(i)))     //Finds ticket with matching PNR
	{
		if(i.pnr==pnrcpy)
		{
			processing();
			displaytkt(i);
			found++;
			break;
		}
	}
	if(found==0)
	{
		clrscr();
		gotoxy(32,13);
		cout<<"No Match Found!!";
		getch();
	}
}
void fare_calc()                           //Calculates an approx. fare for
{                                          //given distance
	IR i;
	int tno, sfcharge=0;
	clrscr();
	border();
	gotoxy(24,4);
	cout<<"F A R E  C A L C U L A T O R  (Beta)";
	gotoxy(21,5);
	cout<<"________________________________________";
	gotoxy(30,7);
	cout<<"Train No.	: ";
	cin>>tno;
	gotoxy(30,9);
	cout<<"From	: ";
	gets(i.from);
	gotoxy(30,11);
	cout<<"To		: ";
	gets(i.to);
	gotoxy(30,13);
	cout<<"Kilometers	: ";
	cin>>i.km;
	gotoxy(30,15);
	cout<<"Class	: ";
	gets(i.cls);
	i.nop=1;
	i.calc_amount();
	if(tno/1000==12 || tno/1000==22 || tno/1000==20)
		sfcharge=20;
	gotoxy(30,20);
	for(int j=1;j<=20;j++)
		cout<<"-";
	gotoxy(30,21);
	cout<<"³ Fare:";
	gotoxy(38,21);
	cout<<setw(10)<<i.amount+sfcharge;
	gotoxy(49,21);
	cout<<"³"<<endl;
	gotoxy(30,22);
	for(j=1;j<=20;j++)
		cout<<"-";
	getch();
}
int cncl_calc(IR &i)                 //Finds and returns cancellation charge
{
	int charge;
	if(strcmpi(i.cls,"SL")==0)
		charge=30;
	else if(strcmpi(i.cls,"3AC")==0)
		charge=60;
	else if(strcmpi(i.cls,"2AC")==0)
		charge=80;
	else if(strcmpi(i.cls,"CC")==0)
		charge=70;
	else if(strcmpi(i.cls,"1AC")==0)
		charge=130;
	else if(strcmpi(i.cls,"2S")==0)
		charge=20;
	return charge;
}
void cancelled(IR i)
{
	processing();
	i.blanktkt();
	fstream t;
	train trn;
	t.open("TRAIN.DAT", ios::in | ios::binary);
	delay(200);
	gotoxy(9,9);
	cout<<"887860"<<i.pnr;
	delay(200);
	gotoxy(26,9);
	cout<<i.tno<<"      "<<i.date<<"   "<<i.km;
	delay(200);
	gotoxy(10,13);
	cout<<i.cls;
	delay(200);
	gotoxy(22,13);
	puts(i.from);
	delay(200);
	gotoxy(40,13);
	puts(i.to);
	for(int j=0;j<3;j++)
	{
		delay(200);
		gotoxy(14,17+j);
		cout<<"CANCELLED";
	}
	delay(200);
	gotoxy(57,17);
	int cnclcharge=cncl_calc(i);
	if(strcmpi(i.quota,"Tatkal")==0||strcmpi(i.quota,"Premium Tatkal")==0)
		cout<<"  00";
	else
		cout<<i.amount-(i.nop*cnclcharge);   //Shows the refund
	while(t.read((char*)&trn,sizeof(trn)))
		if(i.tno==trn.rtntno())
		{
			gotoxy(35,21);
			trn.displaytrain();
		}
}
void cancel()                                     //Cancel the ticket with
{                                                 //matching PNR provided by
	int pnrno,cnt=0,check=0;                        //the user
	IR i;
	fstream f,m;
	f.open("PRS.DAT",ios::in | ios::binary);
	while(f.read((char*)&i,sizeof(i)))
	{
		check=1;
		break;
	}
	f.close();
	clrscr();
	border();
	if(check==0)
	{
		gotoxy(32,13);
		cout<<"NO TICKETS TO CANCEL";
	}
	else
	{
		gotoxy(20,13);
		cout<<"Enter Last 4 Digits of PNR	:887860";
		cin>>pnrno;
		f.open("PRS.DAT", ios::in | ios::binary);
		m.open("CPRS.DAT", ios::out | ios::binary);
		while(f.read((char*)&i, sizeof(i)))             //writes all data in new file except that one which is to be deleted
		{
			if(i.pnr!=pnrno)
				m.write((char*)&i, sizeof(i));
			else
			{
				cnt++;
				cancelled(i);
				i.avbl+=i.nop;
			}
		}
		f.close();
		m.close();
		remove("PRS.DAT");
		rename("CPRS.DAT","PRS.DAT");
		if(cnt==0)                             //If PNR doesn't gets matched
		{                                      //with any one of the PNR's in
			clrscr();                      //database
			gotoxy(32,13);
			cout<<"No Match Found!!";

		}
	}
	getch();
}
void avblcalc()
{
	IR i,c;
	int m=0,nopiec=0;
	train trn;
	clrscr();
	border();
	gotoxy(23,2);
	cout<<"-----------------------------------";
	gotoxy(24,3);
	cout<<"S E A T   A V A I L A B I L I T Y";
	gotoxy(23,4);
	cout<<"-----------------------------------";
	fstream f,t;
	f.open("PRS.DAT", ios::in | ios::binary);
	t.open("TRAIN.DAT", ios::in | ios::binary);
	gotoxy(10,6);
	cout<<"Train Number                : ";
	cin>>i.tno;
	while(t.read((char*)&trn,sizeof(trn)))
		if(i.tno==trn.rtntno())
		{
			gotoxy(50,6);
			trn.displaytrain();
		}
	gotoxy(10,8);
	cout<<"Origin                      : ";
	gets(i.from);
	gotoxy(10,10);
	cout<<"Destination                 : ";
	gets(i.to);
	gotoxy(10,12);
	cout<<"Date of Journey(DD-MM-YY)   : ";
	gets(i.date);
	gotoxy(10,14);
	cout<<"Class                       : ";
	gets(i.cls);
	gotoxy(10,16);
	cout<<"Quota                       : ";
	gets(i.quota);
	i.ttlavbl();
	int seats=i.avbl;
	while(f.read((char*)&c, sizeof(c)))
	{
		if((strcmpi(c.cls,i.cls)==0) && (c.tno==i.tno) && (strcmpi(c.quota,i.quota)==0) && (strcmpi(c.date,i.date)==0))
			for(int k=0;k<c.nop;k++)
				i.avbl=c.avbl;
	}
	coach_allot(m,i);
	i.berthallot(m);
	gotoxy(33,20);
	if(strcmpi(i.pass[m].coach,"RAC")==0 || strcmpi(i.pass[m].coach,"WL")==0)
		cout<<i.pass[m].coach<<"        :"<<abs(i.avbl);
	else
		cout<<"Available :"<<i.avbl;
	getch();
}
void heading()                       //Prints the heading for 6th Menu Option
{
	gotoxy(28,3);
	cout<<"T R A I N  D A T A B A S E";
	gotoxy(27,4);
	cout<<"----------------------------";
}
void addtrain()                                  //Adds a new train info to Database
{
	char ch;
	train t;
	clrscr();
	border();
	fstream g;
	heading();
	g.open("TRAIN.DAT", ios::app  | ios::binary);
	gotoxy(13,5);
	cout<<"Train Number                     :";
	cin>>t.tno;
	gotoxy(13,7);
	cout<<"Train Name                       :";
	gets(t.tname);
	gotoxy(13,9);
	cout<<"Source                           :";
	gets(t.sou);
	gotoxy(13,11);
	cout<<"Destination                      :";
	gets(t.dest);
	gotoxy(13,13);
	cout<<"Average Speed                    :";
	cin>>t.avgspd;
	gotoxy(13,15);
	cout<<"Operating Zone                   :";
	gets(t.zone);
	gotoxy(13,17);
	cout<<"Rake Type(ICF/ICF-CBC/LHB/IRY-20):";
	gets(t.rake);
	gotoxy(13,19);
	cout<<"Loco Links(40 Char.)             :";
	gets(t.llink);
	g.write((char*)&t, sizeof(t));
	g.close();
	clrscr();
	border();
	heading();
	gotoxy(30,13);
	cout<<"Data Sent Successfully";
}
void showtraindb()                                //Shows the train details by
{                                             	 //comparing train No.
	fstream f;
	clrscr();
	border();
	long int tnocpy;
	int cnt=0;
	train t;
	heading();
	gotoxy(22,13);
	cout<<"Enter Train No. to Search     : ";
	cin>>tnocpy;
	f.open("TRAIN.DAT", ios::in | ios::binary);
	while(f.read((char*)&t,sizeof(t)))
	{
		if(tnocpy==t.tno)
		{
			clrscr();
			border();
			heading();
			t.display();
			cnt++;
			break;
		}
	}
	if(cnt==0)                       //Displays a msg. if no data matches
	{
		clrscr();
		char ch;
		gotoxy(27,12);
		cout<<"No Match Found in Database\n";
		gotoxy(24,13);
		cout<<"Do you want to add new?(Y/N): ";
		cin>>ch;
		if(ch=='Y' ||ch=='y')
			addtrain();
	}
}                                          	  //Menu for Railfan's Corner
void rfmenu()
{
	clrscr();
	char ch;
	IR i;
	c:
	while(1)
	{
		clrscr();
		border();
		border2();
		gotoxy(40,7);
		cout<<"MENU";
		gotoxy(40,8);
		cout<<"----";
		gotoxy(31,10);
		cout<<"1.New Train Database";
		gotoxy(31,12);
		cout<<"2.See Train Database";
		gotoxy(31,14);
		cout<<"3.Main Menu";
		gotoxy(31,16);
		cout<<"4.Exit Program";
		gotoxy(31,20);
		delay(500);
		cout<<"Enter your choice ";       //Makes user enter a choice
		cin>>ch;
		processing();
		if (ch=='1' || ch=='2' || ch=='3'||ch=='4')
		{
			switch(ch)
			{
				case '1':
					{
						addtrain();
						getch();
					}
					break;
				case '2':showtraindb();break;
				case '3':menu();break;
				case '4':exit(0);
			}
		}
		else                		//Makes the user re-enter
		{                      		//value for invalid entry
			clrscr();
			gotoxy(21,13);
			cout<<"Invalid Entry...Press any key to Re-enter";
			getch();
			goto c;
		}
		getch();
	}
}
void H_quota()           		//Prints list of quotas available in PRS and shows details about them
{
	char line[80];
	int i=5;
	clrscr();
	border();
	gotoxy(36,3);
	cout<<"Q U O T A S";
	gotoxy(35,4);
	cout<<"-------------";
	ifstream f("HQUOTA.TXT");
	while(!f.eof())
	{
		if(i==20)
		{
			gotoxy(24,22);
			cout<<"Press Enter to view Next Page...";
			getch();
			i=5;
			clrscr();
			border();
		}
		f.getline(line,75);
		gotoxy(5,i);
		puts(line);
		i++;
		delay(200);
	}
	getch();
}
void H_class()                    //Prints classes and their codes
{
	int i=28;
	clrscr();
	border();
	gotoxy(34,3);
	cout<<"C L A S S E S";
	gotoxy(33,4);
	cout<<"---------------";
	gotoxy(27,7);
	cout<<"CODES           CLASS";
	gotoxy(i,10);
	cout<<"SL          Sleeper Class";
	gotoxy(i,12);
	cout<<"3AC       AC 3 Tier Sleeper";
	gotoxy(i,14);
	cout<<"2AC       AC 2 Tier Sleeper";
	gotoxy(i,16);
	cout<<"1AC        AC First Class";
	gotoxy(i,18);
	cout<<"CC          AC Chair Car";
	gotoxy(i,20);
	cout<<"2S       Second Cls. Sitting";
	for(i=24;i<=57;i++)
	{
		gotoxy(i,6);
		cout<<"-";
		gotoxy(i,8);
		cout<<"-";
		gotoxy(i,21);
		cout<<"-";
		delay(200);
	}
	for(i=7;i<=20;i++)
	{
		gotoxy(24,i);
		cout<<"³";
		gotoxy(34,i);
		cout<<"³";
		gotoxy(57,i);
		cout<<"³";
		delay(200);
	}
	getch();
}
void H_LocoNM()              //Finds the meaning of the Loco Name entered
{
	clrscr();
	border();
	char lnm[10];
	gotoxy(25,3);
	cout<<"L O C O  N O M E N C L A T U R E";
	gotoxy(24,4);
	cout<<"__________________________________";
	gotoxy(4,6);
	cout<<"Ever wondered that what the characters written on a Loco mean? Try this..";
	gotoxy(23,7);
	cout<<"Enter Loco Name (BG Only) : ";
	gets(lnm);
	processing();
	clrscr();
	border();
	if(lnm[0]=='W')
	{
		gotoxy(25,10);
		cout<<" W - Broad Gauge (1.676 mtrs)";
		delay(500);
		gotoxy(25,12);
		if(lnm[1]=='D')
			cout<<" D - Diesel Locomotive";
		else if(lnm[1]=='A')
			cout<<" A - AC Electric Locomotive";
		else if(lnm[1]=='C' && lnm[2]!='A')
			cout<<" C - DC Electric Locomotive";
		else if(lnm[1]=='C' && lnm[2]=='A')
		{
			cout<<"CA - AC + DC (Bi-Current) Loco";
			delay(500);
			gotoxy(25,14);
			if(lnm[3]=='M')
				cout<<" M - Mixed (Pass + Freight)";
			else if(lnm[3]=='G')
				cout<<" G - Freight Traction";
			else
			{
				clrscr();
				border();
				cout<<" Error!!! Loco does not exist...";
				getch();
				exit(0);
			}
			delay(500);
			gotoxy(25,16);
			if(lnm[4]=='1'||lnm[4]=='2'||lnm[4]=='3')
				cout<<" "<<lnm[4]<<"- *Denotes Loco Version*";
			else
			{
				cout<<" Error!!! Loco does not exist...";
				getch();
				exit(0);
			}
			delay(100);
			gotoxy(25,18);
			if(lnm[5]=='P')
				cout<<" P - Fit for Passenger";
			else if(lnm[5]!='\0')
			{
				cout<<" Error!!! Loco does not exist...";
				getch();
				exit(0);
			}
			goto nxt;
		}
		else
		{
			cout<<" Error!!! Loco does not exist...";
			getch();
			exit(0);
		}
		delay(500);
		gotoxy(25,14);
		if(lnm[2]=='P')
			cout<<" P - Passenger Hauler";
		else if(lnm[2]=='G')
			cout<<" G - Goods Hauler";
		else if(lnm[2]=='M')
			cout<<" M - Mixed Traction (Pass. + Freight)";
		else if(lnm[2]=='S')
			cout<<" S - Shunter Locomotive";
		else
		{
			cout<<" Error!!! Loco does not exist...";
			getch();
			exit(0);
		}
		delay(500);
		gotoxy(25,16);
		if(lnm[3]=='1')
		{
			if(lnm[4]=='2')
			{
				cout<<"12 - 12000 HP";
				getch();
				exit(0);
			}
			else
				cout<<" 1 - 1000+ HP";
		}
		else if(lnm[3]=='2')
			cout<<" 2 - 2000+ HP";
		else if(lnm[3]=='3')
			cout<<" 3 - 3000+ HP";
		else if(lnm[3]=='4')
			cout<<" 4 - 4000+ HP";
		else if(lnm[3]=='5')
			cout<<" 5 - 5000+ HP";
		else if(lnm[3]=='7' ||lnm[3]=='9'||lnm[3]=='6')
			cout<<" "<<lnm[3]<<" - *Denotes Loco Version*";
		else
		{
			cout<<" Error!!! Loco does not exist...";
			getch();
			exit(0);
		}
		delay(500);
		gotoxy(25,18);
		if(lnm[4]=='D' && lnm[1]=='D' && lnm[2]=='P'|| lnm[4]=='D' && lnm[1]=='D' && lnm[2]=='G')
			cout<<" D - Dual Cab Locomotive";
		else if(lnm[4]=='A'||lnm[4]=='B'||lnm[4]=='C'||lnm[4]=='E'||lnm[4]=='F'||lnm[4]=='G'||lnm[4]=='H'||lnm[4]=='M'||lnm[4]=='D'||lnm[4]=='R')
			cout<<" "<<lnm[4]<<" - *Denotes Sub Class*";
		else if(lnm[5]!='\0')
		{
			cout<<" Error!!! Loco does not exist...";
			getch();
			exit(0);
		}
	}
	else
	{
		clrscr();
		gotoxy(25,13);
		cout<<"Please Enter a Valid Loco Name";
	}
	nxt:
	getch();
}
void H_Tips()                   //Prints some helpful travelling tips
{
	char line[80];
	int i=5;
	clrscr();
	border();
	gotoxy(33,3);
	cout<<"R A I L  T I P S";
	gotoxy(32,4);
	cout<<"------------------";
	ifstream f("H_TIPS.TXT");
	while(!f.eof())
	{
		if(i==20)
		{
			gotoxy(24,22);
			cout<<"Press Enter to view Next Page...";
			getch();
			i=5;
			clrscr();
			border();
		}
		f.getline(line,75);
		gotoxy(5,i);
		puts(line);
		i++;
		delay(200);
	}
	getch();
}
void miscmenu()                      //menu for the miscellaneous option
{
	char ch;
	d:
	while(1)
	{
		clrscr();
		border();
		border2();
		gotoxy(40,7);
		cout<<"MENU";
		gotoxy(40,8);
		cout<<"----";
		gotoxy(33,10);
		cout<<"1.Quotas Available";
		gotoxy(33,11);
		cout<<"2.Travelling Classes";
		gotoxy(33,12);
		cout<<"3.Loco Nomenclature";
		gotoxy(33,13);
		cout<<"4.Travel Tips";
		gotoxy(33,14);
		cout<<"5.Main Menu";
		gotoxy(33,15);
		cout<<"6.Exit Program";
		gotoxy(33,20);
		delay(500);
		cout<<"Enter your choice ";
		cin>>ch;
		processing();
		if (ch=='1' || ch=='2' || ch=='3' || ch=='4' || ch=='5' || ch=='6' || ch=='7')
		{
			switch(ch)
			{
				case '1':H_quota();break;
				case '2':H_class();break;
				case '3':H_LocoNM();break;
				case '4':H_Tips();break;
				case '5':menu();break;
				case '6':exit(0);break;
			}
		}
		else
		{
			clrscr();
			gotoxy(21,13);
			cout<<"Invalid Entry...Press any key to Re-enter";
			getch();
			goto d;            //Goes to the label 'd'
		}
	}
}
void menu()                                  //Main Menu
{
	char ch;
	int n;
	a:
	while(1)
	{
		clrscr();
		border();
		gotoxy(36,3);
		border2();
		gotoxy(40,7);
		cout<<"MENU";
		gotoxy(40,8);
		cout<<"----";
		gotoxy(33,10);
		cout<<"1.New Ticket";
		gotoxy(33,11);
		cout<<"2.Search by PNR";
		gotoxy(33,12);
		cout<<"3.Show Tickets";
		gotoxy(33,13);
		cout<<"4.Cancel Ticket";
		gotoxy(33,14);
		cout<<"5.Fare Calculator";
		gotoxy(33,15);
		cout<<"6.RailFan's Corner";
		gotoxy(33,16);
		cout<<"7.Miscellaneous";
		gotoxy(33,17);
		cout<<"8.AVBL Calculator";
		gotoxy(33,18);
		cout<<"9.Exit Program";
		gotoxy(32,20);
		delay(500);
		cout<<"Enter your choice ";
		cin>>ch;
		processing();
		if (ch=='1' || ch=='2' || ch=='3' || ch=='4' || ch=='5' || ch=='6' || ch=='7'||ch=='8'||ch=='9')
		{
			switch(ch)
			{
				case '1':newtkt();break;
				case '2':searchbypnr();break;
				case '3':showalltkt();break;
				case '4':cancel();break;
				case '5':fare_calc();break;
				case '6':rfmenu();break;
				case '7':miscmenu();break;
				case '8':avblcalc();break;
				case '9':exit(0);
			}
		}
		else
		{
			clrscr();
			gotoxy(21,13);
			cout<<"Invalid Entry...Press any key to Re-enter";
			getch();
			goto a;            //Goes to the label 'a'
		}
	}
}
int password()                       //Allows user to enter security password
{
	int atmpt=1,i;
	char pass[8],pswd[]="IR-PRS18";
	p:
	i=0;
	clrscr();
	border();
	gotoxy(31,12);
	cout<<"PASSWORD: ";
	while(i<8)
	{
		pass[i]=getch();        //Prints star (*) instead of char entered
		cout<<"*";
		i++;
	}
	atmpt++;
	for(i=0;i<8;i++)               //matches the user's password with the original
	{
		if(pass[i]!=pswd[i])
		break;

	}                            //Gives 3 tries to enter password
	if(atmpt<=3)
	{
		if(i==8)
			return 1;
		else
		{
			gotoxy(17,13);
			cout<<"Incorrect Password...Press any key to Re-Enter";
			getch();
			goto p;
		}
	}
	else                     //Exits the program after 3 incorrect password entries
	{
		clrscr();
		gotoxy(23,14);
		cout<<"Entered Incorrect Password 3 Times";
		gotoxy(31,15);
		cout<<"Exiting in ";
		for(i=3;i>=0;i--)           //timer loop
		{
			gotoxy(43,15);
			cout<<i<<" secs.";
			delay(1000);
		}
		return 0;
	}
}
void main()
{
	textcolor(BLACK);            //changes font colour
	textbackground(WHITE);       //changes background colour
	int check;
	check=password();
	if(check==1)
	{
		clrscr();
		border();
		randomize();                     //selects random delay
		int i,dly=random(60-10+1)+10;
		for(i=0;i<=100;i++)              //Loop to print Loading %
		{
			gotoxy(35,13);
			cout<<"Loading..."<<i<<"%";
			delay(dly);
		}
		menu();
	}
	else
		exit(0);
}
//Made by "Keval H.Ambasana"