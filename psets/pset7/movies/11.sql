-- https://cs50.harvard.edu/x/2022/psets/7/movies/

SELECT m.title
FROM
    movies m JOIN stars s JOIN ratings r
ON
    m.id = s.movie_id AND
    m.id = r.movie_id
WHERE
    s.person_id = (
        SELECT id
        FROM people
        WHERE name = "Chadwick Boseman"
    )
ORDER BY r.rating DESC
LIMIT 5;
