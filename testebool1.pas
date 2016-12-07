program testebool1(input, output);
var b : boolean;
   a  : integer;
begin
   b := a>10; 
   b := True = True;
   b := True = (a>10);
   while (b) do
      if (b) then
         b:=False;
   b:=1+2;
end.
