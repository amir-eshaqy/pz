      
   %   *       A   m   i   r   _   e   s   h   a   q   y      
      
   %           t   e   l   e   g   r   a   m       =       a   m   i   r   _   e   s   h   a   q   y      
   %   *       g   m   a   i   l       =       a   m   i   r   9   3   3   6   1   4   6   4   3   3   @   g   m   a   i   l   .   c   o   m      
      
   %   *       S   c   h   e   m   a   t   i   c       a   n   d       t   u   t   o   r   i   a   l       f   i   l   e   s       o   n       G   i   t   H   u   b      
   %           G   i   t   H   u   b       =       h   t   t   p   s   :   /   /   g   i   t   h   u   b   .   c   o   m   /   a   m   i   r   -   e   s   h   a   q   y   /   p   z      
      
   c   l   e   a   r       a   l   l      
   c   l   o   s   e       a   l   l      
   c   l   c      
   d   e   l   e   t   e   (   i   n   s   t   r   f   i   n   d   )   ;      
   a   r   d   u   i   n   o   =   s   e   r   i   a   l   (   '   C   O   M   1   2   '   )   ;      
   s   e   t   (   a   r   d   u   i   n   o   ,   '   B   a   u   d   R   a   t   e   '   ,   1   1   5   2   0   0   )   ;      
   f   o   p   e   n   (   a   r   d   u   i   n   o   )   ;      
                   f   o   r       j   =   1   :   9   9   9   9   9                   %   t   k   r   a   r                      
                                   o   u   t   p   u   t       =       '   '   ;      
                                   o   u   t   p   u   t       =       f   s   c   a   n   f   (   a   r   d   u   i   n   o   )   ;          
                           d   i   s   p   (   o   u   t   p   u   t   )      
                                                   d   a   t   a       =       f   s   c   a   n   f   (   a   r   d   u   i   n   o   )   ;      
                                                   c   o   m   m   a   s       =       s   t   r   f   i   n   d   (   d   a   t   a   ,   '   ,   '   )   ;      
                                                   v   o   l   t   a   g   e   (   j   )       =       s   t   r   2   n   u   m   (   d   a   t   a   (   1   :   c   o   m   m   a   s   (   1   )   -   1   )   )   ;      
                                                   c   u   r   r   e   n   t   (   j   )       =       s   t   r   2   n   u   m   (   d   a   t   a   (   c   o   m   m   a   s   (   1   )   +   1   :   c   o   m   m   a   s   (   2   )   -   1   )   )   ;      
                                                   p   o   w   e   r   (   j   )       =       s   t   r   2   n   u   m   (   d   a   t   a   (   c   o   m   m   a   s   (   2   )   +   1   :   c   o   m   m   a   s   (   3   )   -   1   )   )   ;      
                                                   K   W   h   (   j   )       =       s   t   r   2   n   u   m   (   d   a   t   a   (   c   o   m   m   a   s   (   3   )   +   1   :   c   o   m   m   a   s   (   4   )   -   1   )   )   ;      
                                                   f   r   e   q   u   e   n   c   y   (   j   )       =       s   t   r   2   n   u   m   (   d   a   t   a   (   c   o   m   m   a   s   (   4   )   +   1   :   c   o   m   m   a   s   (   5   )   -   1   )   )   ;      
                                                   p   o   w   e   r   _   f   a   c   t   o   r   (   j   )       =       s   t   r   2   n   u   m   (   d   a   t   a   (   c   o   m   m   a   s   (   5   )   +   1   :   e   n   d   )   )   ;      
                                      
                                   %   p   l   o   t                                  
                           s   u   b   p   l   o   t   (   1   ,   2   ,   1   )   ;   p   l   o   t   (   v   o   l   t   a   g   e   ,   '   L   i   n   e   W   i   d   t   h   '   ,   2   )      
                           y   l   i   m   (   [   1   5   0       4   5   0   ]   )      
                           x   l   i   m   (   [   j   -   5   0       j   +   5   0   ]   )      
                                   t   i   t   l   e   (   "   V   O   L   T   A   G   E       =       :   "   +   v   o   l   t   a   g   e   (   1   ,   j   )   )      
                           s   u   b   p   l   o   t   (   1   ,   2   ,   2   )   ;   p   l   o   t   (   c   u   r   r   e   n   t   ,   '   L   i   n   e   W   i   d   t   h   '   ,   2   ,   '   C   o   l   o   r   '   ,   '   r   '   )      
                           y   l   i   m   (   [   0       6   0   ]   )      
                           x   l   i   m   (   [   j   -   5   0       j   +   5   0   ]   )      
                                   t   i   t   l   e   (   "   C   U   R   R   E   N   T       =       "   +   c   u   r   r   e   n   t   (   1   ,   j   )   )      
                                   d   i   s   p   (   '   M   e   a   s   u   r   e   d       f   o   r       t   h   i   s       t   r   i   a   l   '   )   ;      
                                   %       m   o   v   e       o   n       t   o       o   t   h   e   r       t   r   i   a   l      
                       p   a   u   s   e   (   0   .   1   )      
                   e   n   d      
   %       C   l   o   s   e       s   e   r   i   a   l       p   o   r   t      
   f   c   l   o   s   e   (   a   r   d   u   i   n   o   )   ;      
   d   e   l   e   t   e   (   a   r   d   u   i   n   o   )   ;      
   c   l   e   a   r       a   r   d   u   i   n   o   ;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      ��