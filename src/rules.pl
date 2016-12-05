:- dynamic(light/2).
:- dynamic(poop/2).
:- dynamic(walkable/2).
:- dynamic(wind/2).
:- dynamic(visited/2).
:- dynamic(shooted/2).

setVisited(X,Y) :- assert(visited(X,Y)).
setWalkable(X,Y) :- assert(walkable(X,Y)).
setPoop(X,Y) :- assert(poop(X,Y)).
setShooted(X,Y) :- assert(shooted(X,Y)).
setLight(X,Y) :- assert(light(X,Y)).
removeLight(X,Y) :- retractall(light(X,Y)).
removePoop(X,Y) :- retractall(poop(X,Y)).
removeWalkable(X,Y) :- retractall(walkable(X,Y)).
removeWind(X,Y) :- retractall(wind(X,Y)).
removeVisited(X,Y) :- retractall(visited(X,Y)).
removeShooted(X,Y) :- retractall(shooted(X,Y)).

/*If we find the portal*/
portal(X,Y) :- light(X,Y).
runOut(X,Y) :- portal(X,Y).

/*If we are on a Poop, we can shoot*/
safe(X,Y) :- visited(X,Y), not(poop(X,Y)), not(wind(X,Y)).

shootNorth(X,Y) :-
N is Y-1,
poop(X,Y), walkable(X,N), not(shooted(X,N)), not(visited(X,N)).

shootSouth(X,Y) :-
S is Y+1,
poop(X,Y), walkable(X,S), not(shooted(X,S)), not(visited(X,S)).

shootWest(X,Y) :-
W is X-1,
poop(X,Y), walkable(W,Y), not(shooted(W,Y)), not(visited(W,Y)).

shootEast(X,Y) :-
E is X+1,
poop(X,Y), walkable(E,Y), not(shooted(E,Y)), not(visited(E,Y)).

/*Choose next case*/
goNorth(X,Y) :-
N is Y-1,
((safe(X,Y), walkable(X, N)) ;
(wind(X,Y), safe(X,N))).

goSouth(X,Y) :-
S is Y+1,
((safe(X,Y), walkable(X, S)) ;
(wind(X,Y), safe(X,S))).

goWest(X,Y) :-
W is X-1,
((safe(X,Y), walkable(W, Y)) ;
(wind(X,Y), safe(W,Y))).

goEast(X,Y) :-
E is X+1,
((safe(X,Y), walkable(E, Y)) ;
(wind(X,Y), safe(E,Y))).

/*We prefer to discover new cases*/
betterNorth(X,Y) :-
N is Y-1,
goNorth(X,Y), not(visited(X,N)).

betterSouth(X,Y) :-
S is Y+1,
goSouth(X,Y), not(visited(X,S)).

betterWest(X,Y) :-
W is X-1,
goWest(X,Y), not(visited(W,Y)).

betterEast(X,Y) :-
E is X+1,
goEast(X,Y), not(visited(E,Y)).
