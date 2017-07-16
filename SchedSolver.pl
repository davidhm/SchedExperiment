:-include('./prologData.pl').
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
  defineDomains(Vars,1,Domains),
  %writeDomains(1,Domains),
  defineConstraints(Vars,Domains),
  label(Vars).
  %write(Vars),nl.

writeDomains(VarNumber,[X|Domains]):-
  write('Variable '), write(VarNumber), write(': '),
  write(X), nl,
  VarNumber2 is VarNumber + 1,
  writeDomains(VarNumber2,Domains).

writeDomains(_,[]).

defineVars(Vars):-
  latestStartingHour(N),
  length(Vars,N).

defineDomains([S|Vars],Slot,[L|Tail]):-
  findall([Subject,Group],
  class(Slot,Subject,Group),L),
  length(L,M),
  M >= 1,
  S in 1..M,
  Slot2 is Slot + 1,
  defineDomains(Vars,Slot2,Tail).

defineDomains([S|Vars],Slot,[L|Tail]):-
  findall(Slot,class(Slot,_,_),L),
  length(L,M),
  M =:= 0,
  S in 0,
  Slot2 is Slot + 1,
  defineDomains(Vars,Slot2,Tail).

defineDomains([],_,[]).

defineConstraints(Vars,Domains):-
  enforceConsistency(Vars,Domains,1),
  groupsExactlyOnce(Vars,Domains,1).

enforceConsistency(Vars,Domains,Subject):-
  numberOfSubjects(N),
  Subject =< N,
  findall(G,group(Subject,G,_),L),
  forceEqual(Vars,Domains,Subject,L),
  Subject2 is Subject + 1,
  enforceConsistency(Vars,Domains,Subject2).

enforceConsistency(_,_,_).


forceEqual(Vars,Domains,Subject,[G|ListGroups]):-
  findall(Slot,class(Slot,Subject,G),L),
  auxEqual(Vars,Domains,Subject,G,L),
  forceEqual(Vars,Domains,Subject,ListGroups).

forceEqual(_,_,_,[]).

auxEqual(Vars,Domains,Subject,Group,[S|Slots]):-
  iterateThrough(Vars,Domains,Subject,Group,S,Slots),
  auxEqual(Vars,Domains,Subject,Group,Slots).

auxEqual(_,_,_,_,[]).

iterateThrough(Vars,Domains,Subject,Group,First,[X|Rest]):-
  nth1(First,Vars,FirstElement),
  nth1(X,Vars,SecondElement),
  nth1(First,Domains,FirstList),
  nth1(X,Domains,SecondList),
  nth1(FirstIndex,FirstList,[Subject,Group]),
  nth1(SecondIndex,SecondList,[Subject,Group]),
  FirstElement #= FirstIndex #<==> SecondElement #= SecondIndex,
  iterateThrough(Vars,Domains,Subject,Group,First,Rest).

iterateThrough(_,_,_,_,_,[]).

groupsExactlyOnce(Vars,Domains,CurrentSubject):-
  numberOfSubjects(N),
  CurrentSubject =< N,
  findall(G,group(CurrentSubject,G,1),L),
  theoryGroupsCardinality(Vars,CurrentSubject,Domains,L),
  findall(GLab,group(CurrentSubject,GLab,0),L2),
  labGroupsCardinality(Vars,CurrentSubject,Domains,L2),
  CurrentSubject2 is CurrentSubject + 1,
  groupsExactlyOnce(Vars,Domains,CurrentSubject2).

groupsExactlyOnce(_,_,_).

theoryGroupsCardinality(Vars,Subject,Domains,[X|Groups]):-
  findall(Slot,class(Slot,Subject,X),L),
  length(L,M),
  length(Vars,N),
  length(Indicative,N),
  bindIndicativeVars(Vars,Subject,Domains,[X|Groups],Indicative),
  sum(Indicative,#=,M).

labGroupsCardinality(Vars,Subject,Domains,[X|Groups]):-
  findall(Slot,class(Slot,Subject,X),L),
  length(L,M),
  length(Vars,N),
  length(Indicative,N),
  bindIndicativeVars(Vars,Subject,Domains,[X|Groups],Indicative),
  sum(Indicative,#=,M).

bindIndicativeVars(Vars,Subject,Domains,Groups,Indicative):-
  findall([Slot,X],(member(X,Groups),class(Slot,Subject,X)),L),
  forall(member([S,X],L),(
  nth1(S,Vars,V),
  nth1(S,Domains,ListOfClasses),
  nth1(Idx,ListOfClasses,[Subject,X]),
  nth1(S,Indicative,I),
  write('Slot '),write(V),write(' bound to index '),write(Idx),nl,
  V #= Idx #==> I #= 1
  )).

bindIndicativeVars(_,_,_,_,_).

















































