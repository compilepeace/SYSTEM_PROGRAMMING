    
LOGFILE1=log_output_with_mutex
LOGFILE2=log_output_race_condition

T0=0_without_mutex
T1=1_mutex_lock


for i in {1..50}
do
	./$T1 2>> $LOGFILE1
done


for j in {1..50}
do
	./$T0 2>> $LOGFILE2
done 

