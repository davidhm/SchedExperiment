:-include('./fixedPredicates.pl').
:-use_module(library(clpfd)).
/*
Format:
subject(number).
theoryGroup(subject,group).
labGroup(subject,group).
class(subject,group,slot).
Where slot numbers go from 1 (8:00-9:00)
to 13 (20:00-21:00) on monday,
14 to 26 on tuesday, etc.
Predicates for directing optimization:
minimizeLeisureTime.
- Minimizes time spent between classes.
earliestHours.
- Minimizes number of hours between 8:00 and the first hour.
latestHours.
- Maximizes number of hours between 8:00 and the first hour.
*/

subject(S):- numberOfSubjects(N), between(1,N,S).


main:-
  defineVars(Vars),
  defineDomains(Vars,ListSubjects),
  defineConstraints(Vars,ListSubjects),
  label(Vars),
  write(Vars),nl.

defineVars(Vars):-
  totalNumberOfSlots(N),
  length(Vars,N).

defineDomains([Teoria,Lab|Vars],[Subj|ListSubjects]):-
  findall(X,theoryGroup(Subj,X),L1),
  length(L1,N),
  Teoria in 1..N,
  findall(Y,labGroup(Subj,Y),L2),
  length(L2,M),
  Lab in 1..M,
  defineDomains(Vars,ListSubjects).

defineDomains([],[]).

defineConstraints(Vars,ListSubjects):-
  noOverlapping(Vars,ListSubjects).

noOverlapping([Theory,Lab|Vars],[X|ListSubjects]):-
  findall(H1,class(X,Theory,H1),TheoryHours),
  findall(S1-G1,(member(Y1,TheoryHours),class(S1,G1,Y1),S1\=X),IncompatTheory),
  forceDifferent(X-Theory,IncompatTheory,Vars),
  findall(H2,class(X,Lab,H2),LabHours),
  findall(S2-G2,(member(Y2,LabHours),class(S2,G2,Y2),S2\=X),IncompatLab),
  forceDifferent(X-Lab,IncompatLab,Vars),
  noOverlapping(Vars,ListSubjects).

noOverlapping([],[]).

forceDifferent(Subj-Group,[S-G|Incompat],Vars):-
  isTheoryGroup(G),
  IndexOther is (S-1)*2+1,
  nth1(IndexOther,Vars,OtherVar),
  isTheoryGroup(Group),
  IndexOrig is (Subj-1)*2+1,
  nth1(IndexOrig,Vars,OrigVar),
  OrigVar #\= Group #\/ OtherVar #\= G,
  forceDifferent(Subj-Group,Incompat,Vars).

forceDifferent(Subj-Group,[S-G|Incompat],Vars):-
  isLabGroup(G),
  IndexOther is S*2,
  nth1(IndexOther,Vars,OtherVar),
  isTheoryGroup(Group),
  IndexOrig is (Subj-1)*2+1,
  nth1(IndexOrig,Vars,OrigVar),
  OrigVar #\= Group #\/ OtherVar #\= G,
  forceDifferent(Subj-Group,Incompat,Vars).

forceDifferent(Subj-Group,[S-G|Incompat],Vars):-
  isTheoryGroup(G),
  IndexOther is (S-1)*2+1,
  nth1(IndexOther,Vars,OtherVar),
  isLabGroup(Group),
  IndexOrig is Subj*2,
  nth1(IndexOrig,Vars,OrigVar),
  OrigVar #\= Group #\/ OtherVar #\= G,
  forceDifferent(Subj-Group,Incompat,Vars).

forceDifferent(Subj-Group,[S-G|Incompat],Vars):-
  isLabGroup(G),
  IndexOther is S*2,
  nth1(IndexOther,Vars,OtherVar),
  isLabGroup(Group),
  IndexOrig is Subj*2,
  nth1(IndexOrig,Vars,OrigVar),
  OrigVar #\= Group #\/ OtherVar #\= G,
  forceDifferent(Subj-Group,Incompat,Vars).

forceDifferent(_,[],_).
