set title 'Break-Even Analysis'
set xlabel 'Quantity'
set ylabel 'Amount'
set grid
plot 'results.txt' using 1:2 title 'Revenue' with lines, \
     'results.txt' using 1:3 title 'Cost' with lines, \
     'results.txt' using 1:4 title 'Profit' with lines
pause -1 'Press any key to continue...'
