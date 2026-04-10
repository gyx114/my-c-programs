#include <stdio.h>
int main()
{
	int n;
	scanf("%d",&n);
	getchar(); //»º³åÇø²ĞÁô\n 
	char str[1000];
	int a[1000];
	int s1=0;
	char s[1000];
	int s2=0;
	int b[1000];
	int s3=0;
	for(int i=0;i<n;i++)
	{
		scanf("%c",&str[i]);
	}
	for(int i=0;i<n;i++)
	{
		if(str[i]>='0'&&str[i]<='9')
		{
			a[s1]=str[i]-'0';
			s1++;
			
		}
		else if(str[i]>='a'&&str[i]<='z')
		{
			s[s2]=str[i];
			b[s2]=str[i]-'a';
			s2++;
			
		}
		else if(str[i]>='A'&&str[i]<='Z')
		{
			s[s2]=str[i];
			b[s2]=str[i]-'A';
			s2++;
			
		}
		
	}
	for(int i=0;i<s1-1;i++)
	{
		for(int j=0;j<s1-1-i;j++)
		{
			if(a[j]>a[j+1])
			{
				int temp=a[j];
				a[j]=a[j+1];
				a[j+1]=temp;
			}
		}
	}
	for(int i=0;i<s2-1;i++)
	{
		for(int j=0;j<s2-1-i;j++)
		{
			if(b[j]>b[j+1])
			{
				
				char temp=s[j];
				s[j]=s[j+1];
				s[j+1]=temp;
				int d=b[j];
				b[j]=b[j+1];
				b[j+1]=d;
			}
		}
	}
	for(int i=0;i<s2-1;i++)
	{
		for(int j=0;j<s2-1-i;j++)
		{
			if((b[j]==b[j+1])&&(s[j]<s[j+1]))
			{
				char temp=s[j];
				s[j]=s[j+1];
				s[j+1]=temp;
			}
		}
	}
	
		for(int i=n;i>=0;i--)
	{
		if(str[i]>='0'&&str[i]<='9')
		{
			str[i]=a[s1-1]+'0';
			s1--;
			
		}
		else if(str[i]>='a'&&str[i]<='z')
		{
			str[i]=s[s2-1];
			s2--;
			
		}
		else if(str[i]>='A'&&str[i]<='Z')
		{
			str[i]=s[s2-1];
			s2--;
			
		}
		
	}
	for(int i=0;i<n;i++)
		{
			printf("%c",str[i]);
		 } 
	
	return 0;
	
	
	
	
	
	
	
	
}
