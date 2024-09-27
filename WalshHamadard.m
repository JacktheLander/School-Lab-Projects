function [H] = WalshHamadard(n)

if n==1
    H = [1 1; 1 -1];
else
    
    h = WalshHamadard(n-1);
    H=[h h; h -h];
end

end
