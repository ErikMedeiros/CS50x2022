-- https://cs50.harvard.edu/x/2022/psets/7/movies/

SELECT m.title
FROM
    movies m JOIN stars s
ON
    m.id = s.movie_id
WHERE
    s.person_id IN (
        SELECT id
        FROM people
        WHERE name IN ("Johnny Depp", "Helena Bonham Carter")
    )
GROUP BY s.movie_id
HAVING COUNT(DISTINCT(s.person_id)) = 2
