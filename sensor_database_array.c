#include<stdio.h>
#include<string.h>
#define S_SIZE 20     
#define CR_SIZE 300      
#define RECORDS 24
#define AQI_SIZE 20
#define AQI_RECORDS 300

struct Sensor_database
{
	int sensor_id;
	char sensor_type[20];
	char sensor_loc[20];
	int duration;               //Duration in mins
	int nearby_sensors[20];     
};

struct Date
{
	int day;
	int month;
	int year;
};

struct central_repository 
{
	int sensor_id;
	char sensor_type[20];
	struct Date date;
	float time[RECORDS];
	float data[RECORDS];			
};
struct entity           
{
	int PM10;
	int PM10_time;         //time interval in hours
	int PM25;
	int PM25_time;
	int Ozone_level;
	int OL_time;
}; 
struct Air_Quality_Index
{
	int sensor_id;
	struct entity e[AQI_RECORDS];
	char sensor_loc[20];
	struct Date date[AQI_RECORDS];
	int final_AQI[AQI_RECORDS];
};



void Retrieve_info(struct central_repository s_data[],int size);
void find_communicating_neighbours(struct Sensor_database s[],int size,int id);	
void max_AQI(struct Air_Quality_Index AQI[],int size4 );
void health_status(struct Air_Quality_Index AQI[],int size5);
void check_status(struct Air_Quality_Index AQI[],int size6);
int main()
{
	int i,j,k,day1,month1,ns,l,id;
	struct Sensor_database sensors[S_SIZE];
	struct central_repository sensor_data[CR_SIZE];
	struct Date date;
	struct Air_Quality_Index AQI[AQI_SIZE];
	struct entity e;

	printf("Enter sensor database\n");
	for(i=0;i<S_SIZE;i++)
	{
		printf("Enter sensor-id\n");
		scanf("%d",&sensors[i].sensor_id);
		
		printf("Enter sensor type\n");
		scanf("%s",&sensors[i].sensor_type);
		
		printf("Enter sensor location\n");
		scanf("%s",&sensors[i].sensor_loc);
		
		printf("Enter duration\n");
		scanf("%s",&sensors[i].duration);
		
		printf("Enter total no. of nearby sensors hich are within a range of 1000m\n");
		scanf("%d",&ns);            //if there is no nearby sensors enter 0
		
		printf("enter sensor_id\n");
		for(l=0;l<ns;l++)
		{
			scanf("%d",&sensors[i].nearby_sensors);    //enter last input as 0 after inserting all nearby sensor_id     
		}
		if(ns==0)
		{
			sensors[i].nearby_sensors[0]=0;         // when there is no nearby sensor
		}
	}
	
	
	printf("Enter data for central repository\n");	
	for(j=0;j<CR_SIZE;j++)           
	{
		printf("Enter sensor-id\n");
		scanf("%d",&sensor_data[j].sensor_id);
		
		printf("Enter sensor type\n");
		scanf("%s",&sensor_data[j].sensor_type);
		
		printf("Enter date\n");
		scanf("%d %d %d",&sensor_data[j].date.day,&sensor_data[j].date.month,&sensor_data[j].date.year);
		
		printf("Enter time and Data respectively\n");
		for(k=0;k<RECORDS;k++)
		{
			scanf("%f",&sensor_data[j].time);
			scanf("%f",&sensor_data[j].data);
		}
		
		
	}
	Retrieve_info(sensor_data,CR_SIZE);
	printf("Enter sensor-id to check nearby sensors\n");
	scanf("%d",&id);
	find_communicating_neighbours(sensors,S_SIZE,id);
	max_AQI(AQI,AQI_SIZE);
	health_status(AQI,AQI_SIZE);
	check_status(AQI,AQI_SIZE);
	
}
void Retrieve_info(struct central_repository s_data[],int size)
{
	int i,j,info,time2,day2,day3,month2,month3,year2,year3,found=0;
	char type[20];
	printf("Enter Method\n");
	printf("press 1 if depending on sensor type (retrieves till date data)\n");
	printf("press 2 if depending on specified date for specific sensor type\n");
	printf("press 31 if depending on specific time interval for specific sensor type and for specified date (single day)\n");
	printf("press 32 if depending on specific time interval for specific sensor type and for specified date range (multiple dates)\n");
	scanf("%d",&info);
	switch (info)
	{
		case 1:
			{
				printf("Enter sensor type\n");
				scanf("%s",&type);
				printf("Enter date\n");
				scanf("%d %d %d",&day2,&month2,&year2);
				for(i=0;i<size;i++)
				{
					if(strcmp(type,s_data[i].sensor_type)==0 && (found==0))
					{
						for(j=0;j<RECORDS;j++)
						{
							printf(" %f",s_data[i].data[j]);
						}
					}
					if((year2==s_data[i].date.year) && (month2==s_data[i].date.month) && (day2==s_data[i].date.day))
					{
						found=1;
					}
				}
				break;
			}
		case 2:
			{
				printf("Enter date\n");
				scanf("%d %d %d",&day2,&month2,&year2);
				printf("Enter sensor type\n");
				scanf("%s",&type);
				for(i=0;i<size && (found==0);i++)
				{
					if((year2==s_data[i].date.year) && (month2==s_data[i].date.month) && (day2==s_data[i].date.day))
					{
						if(strcmp(type,s_data[i].sensor_type)==0)
						{
							for(j=0;j<RECORDS;j++)
							{
								printf(" %f",s_data[i].data[j]);
							}	
							found=1;
						}
					}
				}
				break;
			}
		case 31:
			{
				printf("Enter time interval\n");
				scanf("%f",&time2);
				printf("Enter sensor type\n");
				scanf("%s",&type);
				printf("Enter date for which you have to check data\n");
				scanf("%d %d %d",&day2,&month2,&year2);
				for(i=0;i<size && (found==0);i++)
				{
					if((year2==s_data[i].date.year) && (month2==s_data[i].date.month) && (day2==s_data[i].date.day))
					{
						if(strcmp(type,s_data[i].sensor_type)==0)
						{
							for(j=0;j<RECORDS && (found==0);j++)
							{
								if(time2==(s_data[i].time[j]))
								{
									printf(" %f",s_data[i].data[j]);
									found=1;
								}
							}
						}
					}
				}
				break;
			}
		case 32:
			{
				printf("Enter time interval\n");
				scanf("%f",&time2);
				printf("Enter sensor type\n");
				scanf("%s",&type);
				printf("Enter starting date\n");
				scanf("%d %d %d",&day2,&month2,&year2);
				printf("Enter ending date\n");
				scanf("%d %d %d",&day3,&month3,&year3);
				for(i=0;i<size;i++)
				{
					if((year2<=s_data[i].date.year) && (month2<=s_data[i].date.month) && (day2<=s_data[i].date.day))
					{
						if((year3>=s_data[i].date.year) && (month3>=s_data[i].date.month) && (day3>=s_data[i].date.day))
						{
							if(strcmp(type,s_data[i].sensor_type)==0)
							{
								for(j=0;j<RECORDS && (found==0);j++)
								{
									if(time2==(s_data[i].time[j]))
									{
										printf(" %f",s_data[i].data[j]);
										found=1;
									}
								}
							}		
						}	
					}
				}
				break;
			}
		default:
			{
				printf("wrong method number\n");
				break;
			}	
				
	}
}


void find_communicating_neighbours(struct Sensor_database s[],int size,int id)
{
	int i,j,k;
	for(i=0;i<size;i++)
	{
		if(id == s[i].sensor_id)
		{
			j=0;
			while(s[i].nearby_sensors[j]!=0)
			{
				k = s[i].nearby_sensors[j];
				find_communicating_neighbours(s,size,k);
				printf("%d is a neighbour of %d\n",k,id);
				j++;
			}
		}
	}	
	
}

void max_AQI(struct Air_Quality_Index AQI[],int size4 )
{
	int i,j,max=0,month4,year4;
	for(i=0;i<size4;i++)
	{
		for(j=0;j<AQI_RECORDS;j++)
		{
			if(max<AQI[i].final_AQI[j])
			{
				max = AQI[i].final_AQI[j];
				month4 = AQI[i].date[j].month;
				year4 = AQI[i].date[j].year;
			}
		}
	}
	printf("In %d-%d maximum AQI is recorded",month4,year4);
}

void health_status(struct Air_Quality_Index AQI[],int size5)
{
	int i,j,found=0;
	char status[50],loc5[20];
	printf("Enter health status\n");
	scanf("%s",&status);
	printf("Enter sensor location");
	scanf("%s",loc5);
	for(i=0;i<size5 && (found==0);i++)
	{
		if(strcmp(loc5,AQI[i].sensor_loc)==0)
		{
			found=1;
		}
	}
	if(strcmp(status,"good")==0)
	{
		for(j=0;j<AQI_RECORDS;j++)
			{
				if(AQI[i].final_AQI[j]>=1 && AQI[i].final_AQI[j]<=50)
				{
					printf("date: %d %d %d\n",AQI[i].date[j].day,AQI[i].date[j].month,AQI[i].date[j].year);
				}
			}
	}
	else if(strcmp(status,"Satisfactory")==0)
	{
		for(j=0;j<AQI_RECORDS;j++)
			{
				if(AQI[i].final_AQI[j]>=51 && AQI[i].final_AQI[j]<=100)
				{
					printf("date: %d %d %d\n",AQI[i].date[j].day,AQI[i].date[j].month,AQI[i].date[j].year);
				}
			}
	}
	else if(strcmp(status,"Moderately_polluted")==0)
	{
		for(j=0;j<AQI_RECORDS;j++)
			{
				if(AQI[i].final_AQI[j]>=101 && AQI[i].final_AQI[j]<=200)
				{
					printf("date: %d %d %d\n",AQI[i].date[j].day,AQI[i].date[j].month,AQI[i].date[j].year);
				}
			}
	}
	else if(strcmp(status,"Poor")==0)
	{
		for(j=0;j<AQI_RECORDS;j++)
			{
				if(AQI[i].final_AQI[j]>=201 && AQI[i].final_AQI[j]<=300)
				{
					printf("date: %d %d %d\n",AQI[i].date[j].day,AQI[i].date[j].month,AQI[i].date[j].year);
				}
			}
	}
	else if(strcmp(status,"May_cause_respiratory_illness")==0)
	{
		for(j=0;j<AQI_RECORDS;j++)
			{
				if(AQI[i].final_AQI[j]>=301 && AQI[i].final_AQI[j]<=400)
				{
					printf("date: %d %d %d\n",AQI[i].date[j].day,AQI[i].date[j].month,AQI[i].date[j].year);
				}
			}
	}
	else if(strcmp(status,"Severe")==0)
	{
		for(j=0;j<AQI_RECORDS;j++)
			{
				if(AQI[i].final_AQI[j]>=401 && AQI[i].final_AQI[j]<=500)
				{
					printf("date: %d %d %d\n",AQI[i].date[j].day,AQI[i].date[j].month,AQI[i].date[j].year);
				}
			}
	}
	else if(strcmp(status,"Hazardous")==0)
	{
		for(j=0;j<AQI_RECORDS;j++)
			{
				if(AQI[i].final_AQI[j]>=501)
				{
					printf("date: %d %d %d\n",AQI[i].date[j].day,AQI[i].date[j].month,AQI[i].date[j].year);
				}
			}
	}
}

void check_status(struct Air_Quality_Index AQI[],int size6)
{
	int i,j;
	for(i=0;i<size6;i++)
	{
		for(j=0;j<AQI_RECORDS;j++)
		{
			if(AQI[i].final_AQI[j]>=501)
				{
					printf("date: %d %d %d\n",AQI[i].date[j].day,AQI[i].date[j].month,AQI[i].date[j].year);
				}
		}
	}
}


 
