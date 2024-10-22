

% Parent relationships
parent(john, mary).
parent(john, mike).
parent(susan, mary).
parent(susan, mike).
parent(mary, alice).
parent(mary, bob).
parent(mike, charlie).
parent(james, dave).
parent(james, emma).
parent(dave, frank).

% Gender facts
male(john).
male(mike).
male(bob).
male(charlie).
male(james).
male(dave).
male(frank).

female(susan).
female(mary).
female(alice).
female(emma).


% Sibling relationship
sibling(X, Y) :-
    parent(Z, X),
    parent(Z, Y),
    X \= Y.

% Grandparent relationship
grandparent(GP, GC) :-
    parent(GP, P),
    parent(P, GC).

% Aunt/Uncle relationship
aunt_uncle(AU, N) :-
    sibling(AU, P),
    parent(P, N).

% Cousin relationship
cousin(C1, C2) :-
    parent(P1, C1),
    parent(P2, C2),
    sibling(P1, P2).








