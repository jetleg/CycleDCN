//4*4*2 network
#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<time.h>
int main(){
	int temp = 0;
	int randnum = 0;
	int count = 0;
	int set = 0;
	int flownum = 32;//////// 
	int a[flownum]={0};
	int b[flownum]={0};
	float load =0.8;
	float PTL = 0.5;
	int localnum = 0;
	int restnum = flownum*load;
	int keep = 1;
	int localflow = flownum*PTL;
	//printf("%d",localflow);
	int portperawg = 2;////////
	int torperport = 4;////////
	int matdim = portperawg*torperport;
	int K[matdim][matdim]={0};
    int F[matdim][matdim]={0}; 
	int Z[matdim][matdim]={0};
	int FF[matdim][matdim]={0};
	int i=0;int j=0;int k=0;
 	int InputTor[flownum][2]={0};
 	int OutputTor[flownum]={0};	
 	for(i=0;i<flownum;i++){
 		OutputTor[i]=i+1;
 		InputTor[i][0]=i+1;
 	}
 	int InpAlignOrNot[flownum] = {0};int uu = 0;
	int sendOrNot[flownum] = {0};int intraOrNot[flownum] = {0};float xx=0;float yy= 0;//xx�����Ƿ񷢣�yy�����Ƿ���cluster�� 
 	srand((unsigned)time(NULL)); int FCount=0;
 	int OutAlignOrNot[flownum] = {0};//for(i=0;i<flownum;i++){OutAlignOrNot[i]=0;}
 	for(i=0;i<flownum;i++){
 		xx = (double)rand()/(RAND_MAX+1.0);
 		if(xx<load){sendOrNot[i]=1;}
 		yy = (double)rand()/(RAND_MAX+1.0);
 		if(yy<PTL){intraOrNot[i]=1;}
 		//printf("xx%d:%.5f sendOrNot%d:%d\n",i,xx,i,sendOrNot[i]);
 		//printf("yy%d:%.5f intraOrNot%d:%d\n",i,yy,i,intraOrNot[i]);
 	if(sendOrNot[i]==1){
 		while(InpAlignOrNot[InputTor[i][0]-1]==0&&intraOrNot[i]==1){
 			uu=rand()%(portperawg*torperport)+1+portperawg*torperport*int((InputTor[i][0]-1)/portperawg/torperport);
 			//printf("%d %d\n",InputTor[i][0],uu);
 	    if(uu!=InputTor[i][0]&&OutAlignOrNot[uu-1]==0){
 			InputTor[i][1] = uu;//printf("%d",OutAlignOrNot[uu-1]);
			OutAlignOrNot[uu-1]=1;//ͬ�����޷�ͬ��� 
 			InpAlignOrNot[InputTor[i][0]-1]=1;FCount++;
 			printf("intra:%d %d %d\n",InputTor[i][0],InputTor[i][1],OutAlignOrNot[InputTor[i][1]-1]);
 		}
 		}
 		while(InpAlignOrNot[InputTor[i][0]-1]==0&&intraOrNot[i]==0){
 			uu=rand()%flownum+1;
 			//printf("**%d %d\n",InputTor[i][0],uu);
 		if(OutAlignOrNot[uu-1]==0&&((uu>portperawg*torperport*int((InputTor[i][0]-1)/portperawg/torperport)+matdim)||(uu<portperawg*torperport*int((InputTor[i][0]-1)/portperawg/torperport)+1))){
 			InputTor[i][1] = uu;//printf("%d",OutAlignOrNot[uu-1]);
			OutAlignOrNot[uu-1]=1;
 			InpAlignOrNot[InputTor[i][0]-1]=1;FCount++;
 			printf("inter:%d %d %d\n",InputTor[i][0],InputTor[i][1],OutAlignOrNot[InputTor[i][1]-1]);
 		}
 		}
 	}
}
 printf("***************\n");
	 for(i=0;i<flownum;i++){
	 if(sendOrNot[i]==1){
		printf("%d %d\n",InputTor[i][0],InputTor[i][1]);
	 } 
 	}
 	
 	
	for(i=0;i<matdim;i++){//����FF���� 
		for(j=0;j<matdim;j++){
			F[i][j]=0;
		}
	} 
	int aa = 0;int bb = 0;int RouteOrNotInner[matdim][matdim]={0};
	int routeTable[flownum][5]={0};
    for(i=0;i<flownum;i++){
    	routeTable[i][0]=i;routeTable[i][4]=portperawg+2;//��ʾû���� 
    	if(sendOrNot[i]==1){
    	F[(InputTor[i][0]-1)/torperport][(InputTor[i][1]-1)/torperport]=F[(InputTor[i][0]-1)/torperport][(InputTor[i][1]-1)/torperport]+1;	 
         //printf("input:%d output:%d\n",InputTor[i][0]-1,InputTor[i][1]-1);
         routeTable[i][4]=portperawg+1;//��ʾ������/δ���� 
         routeTable[i][1]=InputTor[i][1]-1;routeTable[i][2]=(InputTor[i][0]-1)/torperport;routeTable[i][3]=(InputTor[i][1]-1)/torperport;
		 aa = routeTable[i][2]+1;bb = routeTable[i][3]+1;
		 if(((aa<3 && bb<3) || (aa<5 && aa>2 && bb<5 && bb>2) || (aa<7 && aa>4 && bb<7 && bb>4) || (aa<9 && aa>6 && bb<9 && bb>6) )&&RouteOrNotInner[aa-1][bb-1]==0){
		 	routeTable[i][4] = portperawg;RouteOrNotInner[aa-1][bb-1]=1;
      }
	 }
	 }
	 //printf("Route Table1:\n");
//	 for(i=0;i<flownum;i++){
//	 	for(j=0;j<5;j++){
//	 		printf("%d ",routeTable[i][j]);
//		 }
//		 printf("\n");
//	 }
     int Fcount = 0;
     for(i=0;i<matdim;i++){
    	printf("[");
    	for(j=0;j<matdim;j++){
    		Fcount = F[i][j]+Fcount;
    		if(j==matdim-1&&i!=matdim-1){
    		printf("%d],\n",F[i][j]);
			}
    		else if(j==matdim-1&&i==matdim-1){
			printf("%d]",F[i][j]);
			}
			else{printf("%d,",F[i][j]);
			} 
    		//printf("%d ",FF[i][j]);
		}
		//printf("\n");4
	}
	for(i=1;i<matdim+1;i++){
		for(j=1;j<matdim+1;j++){//////////
			if((i<3 && j<3) || (i<5 && i>2 && j<5 && j>2) || (i<7 && i>4 && j<7 && j>4) || (i<9 && i>6 && j<9 && j>6) ){ 
			K[i-1][j-1]=1;}			
			else{K[i-1][j-1]=0; } 
		} 
	} 
	
	for(i=0;i<matdim;i++){//����FF���� 
		for(j=0;j<matdim;j++){
			Z[i][j]=F[i][j]-K[i][j];
			if(Z[i][j]>=0){FF[i][j] = Z[i][j];
			}
			else{FF[i][j]=0;
			}
			//printf("%d,",FF[i][j]);
			//count2+=F[i][j];
		}
		//printf("\n");
	} 
	int localCount = 0;
	for(i=1;i<matdim+1;i++){
		for(j=1;j<matdim+1;j++){
			if(((i<3 && j<3) || (i<5 && i>2 && j<5 && j>2) || (i<7 && i>4 && j<7 && j>4) || (i<9 && i>6 && j<9 && j>6) ) && F[i-1][j-1]>0){
				count+=1;localCount+=F[i][j];
			}
		}
	} 
//	printf("count:%d\n",count);
	int cont[Fcount-count][4]={0};int contrank[Fcount-count][4]={0};
	int contindex=0;int contemp = 0;int p=0;int q=0;
	for(i=0;i<matdim;i++){
		for(j=0;j<matdim;j++){
			contemp = 0;
			if(FF[i][j]==1){
				for(p=0;p<matdim;p++){
					for(q=0;q<matdim;q++){
						if(i==p || j==q || ((i/portperawg==p/portperawg) && (j/portperawg==q/portperawg))){
							if(!(i==p&&j==q)){cont[contindex][1]=cont[contindex][1]+FF[p][q];
							}
						}
					} 
				}
				cont[contindex][0]=contindex;
				cont[contindex][2]=i;
				cont[contindex][3]=j;
				if(contindex<Fcount-count){
					contindex = contindex+1;
				}
			}
			else if(FF[i][j]>1){
				for(p=0;p<matdim;p++){
					for(q=0;q<matdim;q++){
						if(i==p || j==q || ((i/portperawg==p/portperawg) && (j/portperawg==q/portperawg))){
						   if(!(i==p&&j==q)){contemp=contemp+FF[p][q];
					        }
						}
					}
				}
			 	for(p=0;p<FF[i][j];p++){
			 		cont[contindex][1]=contemp+FF[i][j]-1;
			 		cont[contindex][0]=contindex;
			 		cont[contindex][2]=i;
			 		cont[contindex][3]=j;
			 		if(contindex<Fcount-count){
			 			contindex=contindex+1;
					 }
				 }
			}
		}
	}
	for(i=0;i<Fcount-count;i++){
		for(j=0;j<4;j++)
		contrank[i][j]=cont[i][j];
	}
	int temp1=0;int temp2=0;int temp3=0;int temp4=0;
	for(i=0;i<Fcount-count;++i){
		for(j=0;j<Fcount-count-i-1;++j){
			if(contrank[j][1]>contrank[j+1][1]){
				temp1=contrank[j][0];
				contrank[j][0]=contrank[j+1][0];
				contrank[j+1][0]=temp1;
			    temp2=contrank[j][1];
				contrank[j][1]=contrank[j+1][1];
				contrank[j+1][1]=temp2;
				temp3=contrank[j][2];
				contrank[j][2]=contrank[j+1][2];
				contrank[j+1][2]=temp3;
				temp4=contrank[j][3];
				contrank[j][3]=contrank[j+1][3];
				contrank[j+1][3]=temp4;
			}
		}
	}
//	for(i=0;i<Fcount-count;i++){
//		for(j=0;j<4;j++){
//			printf("%d ",contrank[i][j]);
//		}
//		printf("\n");
//	}
	printf("***********************************\n***********************\n");
 	int ConfMost = contrank[Fcount-count-1][1];
// 	printf("%d",ConfMost);
  	int conten[Fcount-count][ConfMost][4]={0};
  	int contenindex[Fcount-count] = {0}; int temm1=0;int temm2=0;int temm3=0;int contenindexi=0;
  	for(k=0;k<Fcount-count;k++){
  		for(i=0;i<Fcount-count;i++){
  			if(i!=k&&((cont[k][2]==cont[i][2])||(cont[k][3]==cont[i][3])||((int(cont[k][2]/portperawg)==int(cont[i][2]/portperawg)) && (int(cont[k][3]/portperawg)==int(cont[i][3]/portperawg))))){
  				temm1=cont[i][1];temm2=cont[i][2];temm3=cont[i][3];
  				contenindexi=contenindex[k];
 				conten[k][contenindexi][0]=i;
  				conten[k][contenindexi][1]=temm1;
  				conten[k][contenindexi][2]=temm2;
  				conten[k][contenindexi][3]=temm3;
  				contenindex[k]=contenindex[k]+1;
 			 }
 		 }
 	 }
// 	 for(i=0;i<Fcount-count;i++){
// 	 	printf("the contenmat of flow %d %d %d %d %d is\n",cont[i][0],cont[i][1],cont[i][2],cont[i][3],contenindex[i]);
// 	 	for(j=0;j<ConfMost;j++){
// 	 		for(k=0;k<4;k++){
// 	 			printf("%d ",conten[i][j][k]);
//			  }
//			  printf("\n");
//		  }
//		  printf("******************\n");
//	  }
  int distribute[portperawg][matdim][4]={0};
 int find = 0;
 //int distributeYiweiIndex = 0;
  int distributeSanweiIndex = 0;
 int waitAlign[Fcount-count] = {0};
//printf("%d ",Fcount-count);
 int distributenum=0;int temm4;
 int distributeOrNot = 0;int m =0;int n = 0;
int distribute_temp[portperawg][matdim][4]= {0};

int distributenum_temp = 0; p=0;int timecount = 0;
int distributeYiweiIndex[portperawg]={0};
int waitsearch[Fcount-count] = {0};
for(i=0;i<Fcount-count;i++){
	waitsearch[i]=1;
}
m=0;n=0;
int times = 0;
if((Fcount-count)>2){
	times=(Fcount-count)*0.8;
} 
else{
	times = 1;
}
while(timecount<1){//
//while(timecount<int((Fcount-count)*0.8)){
	timecount=timecount+1;
		 for(i=0;i<portperawg;i++){
 	for(j=0;j<matdim;j++){
 		for(k=0;k<4;k++){
 			distribute_temp[i][j][k]=0;
		 }
	 }
 }
	distributeSanweiIndex=0;
	for(i=0;i<portperawg;i++){
	distributeYiweiIndex[i]=1;
}
	distributenum_temp = 0;
	m=m+1;
    for(i=0;i<Fcount-count;i++){
	waitAlign[i]=1;
}
    for(i=0;i<portperawg;i++){
    for(j=0;j<4;j++){
     distribute_temp[i][0][j]=contrank[i+m-1][j];
    }
    waitAlign[i-1+m]=0; 
    }
    distributenum_temp =distributenum_temp+portperawg;
    for(k=0;k<Fcount-count;k++){
    distributeSanweiIndex = 0;distributeOrNot = 0;
    while(waitAlign[k]==1&&distributeSanweiIndex<portperawg){
    distributeOrNot=1;
    for(i=0;i<distributeYiweiIndex[distributeSanweiIndex];i++){
      for(j=0;j<distribute_temp[distributeSanweiIndex][i][1];j++){
          if(contrank[k][0]==conten[distribute_temp[distributeSanweiIndex][i][0]][j][0]){distributeOrNot=0;}
      }
    }
      if(distributeOrNot==1&&contrank[k][0]!=distribute_temp[0][0][0]){
      for(i=0;i<4;i++){
      distribute_temp[distributeSanweiIndex][distributeYiweiIndex[distributeSanweiIndex]][i]=contrank[k][i];
      }
      waitAlign[k]=0;distributeYiweiIndex[distributeSanweiIndex]++;
      distributenum_temp++;
      }
      distributeSanweiIndex++;
    }
    }
    if(distributenum_temp>distributenum){
    distributenum=distributenum_temp;
     for(i=0;i<portperawg;i++){
 	   for(j=0;j<matdim;j++){
 		for(k=0;k<4;k++){
 			distribute[i][j][k]=distribute_temp[i][j][k];
		 }
	 }
 }
    }
}
     //distributeSanweiIndex=distributeSanweiIndex-1;
     int distributeMatrix[distributeSanweiIndex][matdim][matdim]={0};
     for(k=0;k<distributeSanweiIndex;k++){ 
     for(i=0;i<matdim;i++){
     	for(j=0;j<matdim;j++){
     		distributeMatrix[k][i][j]=0;
     	//	printf("%d,",distributeMatrix[k][i][j]);
			 		 }
	 }
	 } 
	 int distributenum2=0;int distributenum3=0;int routeif=0; 
     for(i=0;i<portperawg;i++){
     	 printf("the distributeSanweiIndex method of %d page:\n",i);
     	for(j=0;j<matdim;j++){
     		printf("%d %d %d %d\n",distribute[i][j][0],distribute[i][j][1],distribute[i][j][2],distribute[i][j][3]);	
 		    if(!(distribute[i][j][0]==0&&distribute[i][j][1]==0&&distribute[i][j][2]==0&&distribute[i][j][3]==0)){distributenum3++;}
 		    //printf("distributenum3:%d\n",distributenum3);
		 }
 		for(j=0;j<matdim;j++){
 			if(!(distribute[i][j][0]==0&&distribute[i][j][1]==0&&distribute[i][j][2]==0&&distribute[i][j][3]==0)){
 				distributeMatrix[i][distribute[i][j][2]][distribute[i][j][3]]++;
 			}
 		}
 		printf("the distribute matrix of %d page:\n",i);
 		for(m=0;m<matdim;m++){
 			for(n=0;n<matdim;n++){
				 if(distributeMatrix[i][m][n]<2){
 				printf("%d ",distributeMatrix[i][m][n]);
				 }
				 else{printf("0 ");
				 }
				 if(distributeMatrix[i][m][n]==1){
					 distributenum2++;routeif=0;k=0;
					 while(routeif==0){
					 	if(sendOrNot[k]==1&&routeTable[k][2]==m&&routeTable[k][3]==n&&routeTable[k][4]==portperawg+1){
						 routeTable[k][4]=i;routeif = 1;
						 }
						 k++;
					 }
				 }
 			}
 			printf("\n");
 		}
 		printf("\n");
 	}
 	printf("Route Table2:\n");
	 for(i=0;i<flownum;i++){
		 //if(sendOrNot[i]==1){
	 	printf("{");
	 	for(j=0;j<5;j++){
	 		if(j!=2&&j!=3){
	 		printf("%d",routeTable[i][j]);}
	 		if(j==4&&i!=flownum-1){printf("},");} else if(j==4&&i==flownum-1){printf("}");}
	 		else{if(j!=2&&j!=3){printf(",");}}
		 }
		 printf("\n");
		 //}
	 }
    printf("\n\n\n\n\n\n\n"); 
int FFcount = 0;
//printf("{");
    for(i=0;i<matdim;i++){
    	printf("[");
    	for(j=0;j<matdim;j++){
    		if(j==matdim-1&&i!=matdim-1){
    		printf("%d],\n",FF[i][j]);
			}
    		else if(j==matdim-1&&i==matdim-1){
			printf("%d]",FF[i][j]);
			}
			else{printf("%d,",FF[i][j]);
			} 
    		//printf("%d ",FF[i][j]);
    		FFcount=FF[i][j]+FFcount;
    		//Fcount = F[i][j]+Fcount;
		}
		//printf("\n");
	} 
	printf("\n\n\n\n\n\n\n"); 
	//printf("*******************\n");
    printf("FCount:%d Fcount:%d throughput:%.4f total:%d\n",FCount,Fcount,double((count+distributenum)*1.0/(FCount*1.0)),distributenum+count);
	//printf("distributrnum_temp:%d distributenum:%d distributenum2:%d distributenum3:%d\n",distributenum_temp,distributenum,distributenum2,distributenum3);
	printf("count:%d distributenum:%d distribute_temp:%d total:%d throughput:%.4f\n",count,distributenum,distribute_temp,count+distributenum,double((count+distributenum)*1.0/(Fcount*1.0)));
	printf("count:%d restnum:%d FCount:%d Fcount:%d Fcount-count:%d FFcount:%d",count,restnum,FCount,Fcount,Fcount-count,FFcount);
	return 0;
} 
