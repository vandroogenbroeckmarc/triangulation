function [ X Y Q ] = triangulationToTal( A1 , A2 , A3 , x1 , y1 , x2 , y2 , x3 , y3 )
% [ X Y Q ] = triangulationToTal( A1 , A2 , A3 , x1 , y1 , x2 , y2 , x3 , y3 )
%
% Version 1.1
%
% Computes the position of a robot (X;Y) that sees three beacons (x1;y1), (x2;y2), and (x3;y3)
% with the angles A1, A2, and A3, respectively.
% The functions also returns an error measure Q of the computed position.
%
% All rights reserved by Vincent Pierlot and Marc Van Droogenbroeck. 
% You are allowed to use the programs and the source code
% for educational purposes and for your own usage only. 
% Distribution or any form of commercial usage is strictly prohibited.
% Please contact the authors if you want to use the program or source
% outside the scope of the allowed usage.

  COT_MAX = 100000000 ; % this constant may be modified

  cot_12 = cot( A2 - A1 ) ;
  cot_23 = cot( A3 - A2 ) ;
  cot_31 = ( 1.0 - cot_12 .* cot_23 ) ./ ( cot_12 + cot_23 ) ;

  cot_12 = saturate_value_to_bounds( cot_12 , COT_MAX ) ;
  cot_23 = saturate_value_to_bounds( cot_23 , COT_MAX ) ;
  cot_31 = saturate_value_to_bounds( cot_31 , COT_MAX ) ;

  x1_ = x1 - x2 ; y1_ = y1 - y2 ; x3_ = x3 - x2 ; y3_ = y3 - y2 ;

  c12x = x1_ + cot_12 * y1_ ;
  c12y = y1_ - cot_12 * x1_ ;

  c23x = x3_ - cot_23 * y3_ ;
  c23y = y3_ + cot_23 * x3_ ;

  c31x = (x3_ + x1_) + cot_31 * (y3_ - y1_) ;
  c31y = (y3_ + y1_) - cot_31 * (x3_ - x1_) ;
  k31 = (x3_ * x1_) + (y3_ * y1_) + cot_31 * ( (y3_ * x1_) - (x3_ * y1_) ) ;

  D = (c12x - c23x) .* (c23y - c31y) - (c23x - c31x) .* (c12y - c23y) ;
  invD = 1.0 ./ D ;
  K = k31 .* invD ;

  X = K .* (c12y - c23y) + x2 ;
  Y = K .* (c23x - c12x) + y2 ;

  Q = abs( invD ) ;

end

% Saturate each element of x to the bounds [-m m]
% x must be a line vector, and m must be positive
function [ y ] = saturate_value_to_bounds( x , m )

  pos = 1 : 1 : length( x ) ;
  z = [ 0 x ] ;

  posh = x > m ;
  z( (pos.*posh) + 1 ) = m ;

  posl = x < -m ;
  z( (pos.*posl) + 1 ) = -m ;
  
  y = z( 2 : end ) ;

end

