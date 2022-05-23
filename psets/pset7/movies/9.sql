-- https://cs50.harvard.edu/x/2022/psets/7/movies/

SELECT p.name
FROM
    movies m JOIN stars s JOIN people p
ON
    m.id = s.movie_id AND
    p.id = s.person_id
WHERE m.year = 2004
ORDER BY p.birth;
