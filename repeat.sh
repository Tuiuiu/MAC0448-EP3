for run in {1..30}
do
  ./simulator entrada_med.txt > /dev/null & pidstat 1 -p $! >> cpu_med.txt
done
