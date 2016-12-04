:- dynamic(light/2).
:- dynamic(poop/2).
:- dynamic(walkable/2).
:- dynamic(wind/2).
:- dynamic(visited/2).

portal(X,Y) :- light(X,Y).

runOut(X,Y) :- portal(X,Y).

safe(X,Y) :- not(poop(X,Y)), not(wind(X,Y)).

shootNorth(X,Y) :-
N is Y-1, W is X+1, S is Y+1, E is X-1, poop(X,Y),
  (poop(X,Y), poop(W, N) ;
   poop(X,Y), poop(E, N) ;
   not(visited(W, N)), not(visited(E, N)), not(visited(W, S)), not(visited(E, S)))
, walkable(X,S).

shootSouth(X,Y) :-
N is Y-1, W is X+1, S is Y+1, E is X-1, poop(X,Y),
  (poop(X,Y), poop(W, S) ;
   poop(X,Y), poop(E, S) ;
   not(visited(W, N)), not(visited(E, N)), not(visited(W, S)), not(visited(E, S)))
, walkable(X,S).

shootWest(X,Y) :-
N is Y-1, W is X+1, S is Y+1, E is X-1, poop(X,Y),
  (poop(X,Y), poop(W, N) ;
   poop(X,Y), poop(W, S) ;
   not(visited(W, N)), not(visited(E, N)), not(visited(W, S)), not(visited(E, S)))
, walkable(W,Y).

shootEast(X,Y) :-
N is Y-1, W is X+1, S is Y+1, E is X-1, poop(X,Y),
  (poop(X,Y), poop(E, N) ;
   poop(X,Y), poop(E, S) ;
   not(visited(W, N)), not(visited(E, N)), not(visited(W, S)), not(visited(E, S)))
, walkable(E,Y).


goNorth(X,Y) :-
N is Y-1,
  (safe(X,Y) ;
  poop(X,Y), not(shootNorth(X,Y));
  wind(X,Y), visited(X,N))
, walkable(X,N).

goSouth(X,Y) :-
S is Y+1,
  (safe(X,Y) ;
  poop(X,Y), not(shootNorth(X,Y));
  wind(X,Y), visited(X,S))
, walkable(X,S).

goWest(X,Y) :-
W is X-1,
  (safe(X,Y) ;
  poop(X,Y), not(shootNorth(X,Y));
  wind(X,Y), visited(W,Y))
, walkable(W,Y).

goEast(X,Y) :-
E is X+1,
  (safe(X,Y) ;
  poop(X,Y), not(shootNorth(X,Y));
  wind(X,Y), visited(E,Y))
, walkable(E,Y).
