-- https://cs50.harvard.edu/x/2022/psets/7/movies/

SELECT p.name
FROM
    movies m JOIN directors d JOIN people p
ON
    m.id = d.movie_id AND
    p.id = d.person_id
WHERE
    m.id IN (
        SELECT movie_id
        FROM ratings
        WHERE rating >= 9.0
    )
