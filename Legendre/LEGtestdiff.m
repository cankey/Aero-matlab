p = 7;

 x = transpose(sin(0.5*pi*linspace(-1,1,p+1)));
 
 V         = LEGvdm(x,p);
 
 Dhat    = LEGdiff(p);
 
 M        = LEGmass(p);

for m=1:8
 F = x.^m; 
 
 Fcoeff      = V\F;
 
 diffFcoeff = (Dhat*Fcoeff);
 
 diffF         = V*diffFcoeff;
 
 error(m) = max(abs((m)*x.^(m-1) - diffF));
 
end

plot(error, 'r*'); hold on; plot(error, 'k-'); hold off;