//int abb = 0, cbb = 0, nn = 7; // skip = 55, var_case1 = 1, var_case5 = 5;

22;

int aa = 5;
int bb = 0;

22;

int isum(double a, int b)
{
	int c = 5;
		
    return a + b;
}


bb = isum(2, 3);

int main()
{
	return isum(6, 7);
}

77; bb; 88; 92; ?
		




if (aa == 1)
	bb = 1;
else if (aa == 2)
	bb = 2;
else if (aa == 3)
{
	bb = 3;
}
else { bb = 4; }

77; aa; 88; bb; 99; ?


int count = 0;


switch (1)
{
	case 1:
		abb = 1;
		cbb = 8;
		break;
	case 2:
		abb = 2;
		break;	
	case 3:
		abb = 3;
		break;
	case 4:
		abb = 4;
		break;
	default:
		abb = 5;
		break;
}

55; abb; 77; cbb; 88; ?

switch (nn)
{
	//default:
	//case 1:
		if (nn > 1) count++; nn-0; nn++; n++;
		abb = 1;
		//break;
	case 2:  
		abb = 2;
		abb = 3;
		while (count < 5)
		{
	//case 3:
		abb++;
		count++;
		}
		//count++;
		abb = abb + 4;
		break;
	default:
		//abb = 5;
		break;
}


8888; count; 7777; abb; 999;

/*
int cbb, abb; 77; 88; 99;

//switch (1) {default: switch (2) break; break;}

switch (2)
{
	case 1:
		cbb = 1;
		//break;
	case 2:
		cbb = 2;
		cbb = 3;
	case 3:
		switch (7) { case 6: abb = 6; case 7: abb = 7; break; case 8: abb = 8; }
		17;
		cbb = 4;
		break;
	case 5:
		cbb = 5;
		break;
}

6666; abb; 444444; cbb; 55555;
*/

int select = 2;

33;

switch (select)
{
	skip = 22;
	896; 789;
	case 1:
		abb = 11;
		//break;
		728; 678; nn = nn + 2; 33;
		var_case1 = 1111;
	case 2:
		abb = 22;
		switch (select)
		{
			case 1:
				cbb = 1;
				break;
			case 2:
				cbb = 2;
				cbb = 3;
			case 3:
				cbb = 4;
				break;
			default:
				cbb = 5;
				break;
		}
		nn = nn + 3;
		//break;
	case 3:
	default:
		abb = 33;
		if (abb - 33)
		{
			nn = nn + 4;
		}
	case 4:
		//break;
		abb = 44;
		break;
		nn = nn + 5;
	case 5:
		var_case5 = 5555;
	default:
	case 6:
		49;
		select = 6666;
		50; 51;
}

88; abb; 89; cbb; 8777; select; 78; skip; 98; nn; 888; var_case1; 888; var_case5; 999;

?

switch (select)
{
	case 1:
		abb = 1;
		break;
	case 2:
		abb = 2;
		abb = 3;
	case 3:
		abb = 4;
		break;
	//default:
		abb = 5;
		break;
}

333;  abb; 444; select; 555;  666;

?


static int count = 1, break_ii = 5, marker = 55;
int local_cnt = 0;
	

do {
	local_cnt++;
	
	if (local_cnt < 20)
		do break; while(1);
	
	count++;
	if (count == break_ii)
	{
		marker = 77;
		continue;
	}
	//count++;

} while (count < 10);

333;  count; 444; break_ii 555; marker; 666;

//count = 3;

88;



?

		
while (count < 10)
{
	count++;
	if (count == break_ii)
	{
		marker = 77;
		continue;
	}
	marker = 99;
	//count++;
}

333;  count; 444; break_ii 555; marker; 666;

?


do {

	if (count == break_ii)
	{
		marker = 77;
		break;
	}
	count++;

} while(count < 10);

333;  count; 444; break_ii 555; marker; 666;

88;

?


while (count < 10)
{
	if (count == break_ii)
	{
		marker = 77;
		break;
	}
	count++;
}

333;  count; 444; break_ii 555; marker; 666;

88;

?

int a = 7;

for (int a=0; a < 3; a++)
{
	count = count + 1;
}

88;

count;

54; a; 55; 57; ?

for ( ; ; )
{
	1;
}

33;  55; ?
		
static int count = 2;

do {
	count = count + 1;
} while (count < 5);


77;

count;
count = 0;

int a = 7;

for (int a=0; a < 3; a++)
{
	count = count + 1;
}

88;

count;

54; a; 55; 57; ?

9999;

{
    int a = 1;
    int b = 5;
    
    for (int a=0 ; a < 3; a++)
    {
        b = b+a;
    }

    a; //1
    b; //8
}

11;  33;

?




static int count = 2;

while (count < 5)
{
	count = count + 1;
}

77;

count;

88;



int loop()
{
	while (count < 5)
	{
		count = count + 1;
	}
}

77;

loop();

777;

count;

55;

int main()
{
	return loop();
}

44;

88;

?






int gaa = 1;
int count = 5;

55;  count; gaa;

int seqfunc(int paa)
{
	//int count = 5;
	count;
	while (count > 3)
	{
		2+3;
		count--;
	}
	return count + ++paa;
	
	//return 1+1+1 + gaa + paa;
}

int main()
{
	seqfunc(2);
	return count;
	return seqfunc(2);
}

77;

//main();

55;

?


/*

int gbb = 2;

gbb = gaa*5 + 3 + gbb;

if (3)
{
	gbb = 725;
}

77; gbb;  55;

//9999;

*/
int seqfunc(int p);
int seqfunc(int pa);

int seqfunc(int paa)
{
    1;
    1+1;
    return 1+1+1 + gaa + paa;
    //1+(gaa+(1+1));
    //1+(1+(1+1));
    //int laa = 1;
    //return 1+(gaa+(1+(1+(1+(1+gaa)))))+laa;
}

77;

int seqfunc(int paaa);

88;


seqfunc(3) + 2;

55; 42;


66; 77;

?

/*

//int gaa = 1;

//int gbb = 2;



int gfunc(int a)
{
    int lla = 1, llb, llc = 2, lld = 3;
    llb = lla + llc;
    int lle;
    int llf = 4;
    return llb + llf;
    //return lcc;
}

gfunc(1);

9999;


int gfunc(int a)
{
    //int lla = 1, llb, llc = 2;
    int laa = 3;
    int lbb = 4;
    int lcc; // = laa + lbb;
    lcc = 2 + laa;
    //return lcc;
    int lla = 1, llb, llc = 2;
    llb = lla + llc + lcc;
    return llb + a;
    //return lcc;
}

gfunc(1) + gaa;


66;

//seqfunc();

67;

9999;

*/


//const static int suljo = 5, fcdec(int a, int b), selma = suljo + 2;
int suljo = 5, fcdec(int a, int b), selma = suljo + 2;

selma;

int ja;

suljo + selma;

ja;

selma;


9999;

int fcdec(int a, int b);
//int fcdec(int c);
//int fcdec(int c, int d, int k);
int fcdec(int c, int d);


int fcdec(int e, int f)
{   
    2+5;
    return e;
}

55;

fcdec(77, 3);

22;

fcdec(88, 3);

9999;


//int fact(int n);

int fact(int n)
{
    if (n)
    {
        return n * fact (n-1);
    }
    else
    {
        return 1;
    }
}

17;

22;

fact(4);

55;
9999;

int cfact(int n)
{
    return fact(n);
}

cfact(4);
cfact(5);


3333;
9999;



extern int bb;

int aa = 2, bb, cc=4;

extern int bb = 2;

aa; bb; cc; 444;

extern int bb;

int ff = 1;

bb;



int localdecl (int a)
{
    
    //extern int ee = 5;
    
    int ee = 10, ldc(int aa, int bb);
    
    extern int ee;
    
    //return ee;
    
    {
        extern int ee;
        
        ee = ee + a;
        
        ee = ee + ff;
        
        2;
        2 + 3;
        1+(1+(1+1));
        3;
        
        ee = ee + ldc(a, 3);
        
        return ee;
    }
}

5555;

ee;

int ee = 22;

//localdecl(2);

ee;

int ldc(int xx, int yy)
{   
    return xx;
}

int clocaldecl(int a)
{
    return localdecl(a);
}

clocaldecl(2);
clocaldecl(3);

ee;

//9999;




int localdeclf(int a, int b)
{
    int ldc(int aa, int bb);
    
    return ldc(a, b);
}

localdeclf(6, 7);

localdeclf(7, 6);


1111;



int emptyparamlist()
{
    return 77;
}

emptyparamlist();


2222222;


int fcdec(int a, int b, int c)
{
    return a;
}

fcdec(2, 3, 4);


111111;

/*

int fcdec(int a);

int fcdec(int a)
{
    return a;
}

fcdec(3);

4444;


int fcdecuse(int a)
{
    return fcdec(a);
}

/*
int fcdec(int a)
{
    return a;
}
*/


fcdecuse(3);

999999;

*/

extern int ee;

ee;

int ff = 1;

int localdecl (int a)
{
    /*
    int c;
    int d = 5;
    
    c;
    d;
    
    int e = 7;
    
    5+3;
    
    e;
    */
    
    int ee = 10;
    
    {
        extern int ee;
        
        ee = ee + a;
        
        ee = ee + ff;
        
        return ee;
    }
}

//ee;

//int ee = 22;

localdecl(2);

ee;



extern int cc =3;

extern int cc;

int cc = 2;

bb;;

cc;

/*
int cc;

int bb = 5;


extern int aa;

extern int aa;

//aa = 2;   //'aa' does not name a type
//aa + 2;   //'aa' does not name a type
//++aa;     //'aa' does not name a type + tobe fixed

int aa;

end com

extern int aa;

int aa = 2;

aa = aa + 1;

aa;

int bb = 4;

//int aa = 8;

//int bb = 3;

//bb=2;
 


bb;

*/


int fact(int n)
{
    if (n)
    {
        return n * fact (n-1);
    }
    else
    {
        return 1;
    }
};

int main(int a)
{
    return fact(4);
}

main(2);

//2 < 5 == 3 > 1; 

//int sulejman(int a, int b);

int funcif (int a, int b)
{
    if (a)
    {
        return a;
    }
    return b;
};

funcif(3,4);


const static int suljo = 5, selma = 7;
int ja;

int sulejman(int a, int b);

suljo;

ja = suljo++ + 3; //8

suljo; //6
ja;    //8

ja = suljo-- - 3; //3

suljo; //5


int mala = 3;
int mama = 20;


mala = 20 + 3 = mama;


mama;

++2;

++mala;

++ ++mama;  //22
++mama;  //23
mama;    //23

--mala;
mala;  //3

--mama; //22
mama = ++mala + 1; //5

mala = -- --mama -2; //1




((10+1+2+3));

!3;

0 || !0;


2.33 + 7.22;

int mala = 3;
int mama = 20;

--mama; //19

mama = ++mala + 1; //5


++mama + mala == mama + ++mala; //1



class A
{
	int a;
	int b;
};

class B
{
	int c;
	A   d;
};

B babo;

babo.d.b;






int a;

int b=34567;

a;
b;

int u=8;

a=b=u;

a=b=120+3;

a; b;

b=7;
a=b;

a=3;

while(a)
{
	b=b+a;
	a=a-1;
}

if (a)
{
	b=b+1;
	b=b+2;
}
else
{
	b=b+1;
	b=b+1;
}


a;
b;

10-1-2-3-4;

10-2;

10-1-2;


((10-1-2-3));

1+2-(3+(4-5));

1-2+(3-(4+5));



2*5;
 
real eee=1.1;

1+1+1+eee*2+3*2;

int ooo=1.1;
1+1+1+ooo*2+3*2;

//analyze this
2.33 + 7.22;

5/2;

int a=5;
int b=2;

a/b;

5.0/2;

int i = 1;
int e = 0;

int ee = 0;

if (i)
{
	i;
}
else
{
	e;
}

int s = 0;

if (e)
{
	i;
	s = 1;
}
else if (e)
{
	e;
	s = 2;
}
else
{
	s = 3;
}

27;
s;


int bbb = 7;
int iii = 8;


{
	bbb = iii + 2;
	bbb;
	iii;
}

{
	bbb;
	{
		iii;
		{
			bbb;
		}
	}
	iii;
}


int aaa = 3;

1;
2;
3;

while (aaa) aaa = aaa-1;

aaa;

aaa = 3;
bbb = 4

int abab = 0;

while (aaa) 
{
	while (bbb)
	{
		abab = abab + 2;
		bbb = bbb-1;
	}
	bbb = 4;
	aaa = aaa-1;
}

17;

aaa;

abab;

+5;

+2 + +5;

-2;

-2 - -3;

5 - -1 + 4;
5 - -1 - 4;
5 - -1 + -4;


! ! ! !0;

! ! !0;

!1;

1 && !0;

0 ||& 0;
1 && 0;
0 && 1;
1 && 1;

0 || 0;
1 || 0;
0 || 1;
1 || 1;



int a = 1;
int b = 2;

int ab = 0;

ab = b = a+4;

{
	a;
	ab;
	a;
	b;
	b=a;
}

ab = a+b+ab;


ab;

a+b;

1+2*2*3+2*(1+1);
1+(1+1);
1+2+(3+(4+5));

10-1-2-3;

1+(2+3);

4+(5+(6+8));
1+(2+3);
3-(2-1);

2*(3+4);

4*(3+2);

5*(7+3);

5-2-1;

int a = 8-1-1-2-3;

int b = (a +1)*a;

a;

b = 5-2-1;

a = b-1;

2*((2+3*3)*2)+1;

1+1;

2*(3+4);

1+1+1+1+1+1+1+1+1+1;

2+3*2;


