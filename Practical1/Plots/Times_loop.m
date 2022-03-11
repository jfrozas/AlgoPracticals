#Times_loop.m

x = [500 1000 2000 4000 8000 16000 32000];

MaxSubSum1 = [887 3532 10946 18486 76969 302299 1205543];

MaxSubSum2 = [1.788 3.312 6.159 8.151 19.3 33.57 66.114];

while (1)

plot(x, MaxSubSum2, "linewidth", 2, "color", 'b', "marker", '*');
pause(3);
hold on;
plot(x, MaxSubSum1, "linewidth", 2, "color", 'r', "marker", '*');
pause(5);
hold off;

endwhile
