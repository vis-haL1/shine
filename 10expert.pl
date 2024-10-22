% Define diseases and their symptoms
disease(flu, fever).
disease(flu, cough).
disease(flu, sore_throat).
disease(cold, cough).
disease(cold, runny_nose).
disease(covid19, fever).
disease(covid19, cough).
disease(covid19, fatigue).

% Check if a disease has a certain symptom
has_symptom(Disease, Symptom) :-
    disease(Disease, Symptom),
    format('~w is a symptom of ~w.~n', [Symptom, Disease]).

% List all symptoms of a disease
list_symptoms(Disease) :-
    findall(Symptom, disease(Disease, Symptom), Symptoms),
    format('The symptoms of ~w are: ~w.~n', [Disease, Symptoms]).
