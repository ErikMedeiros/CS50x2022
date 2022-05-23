-- https://cs50.harvard.edu/x/2022/psets/7/movies/

SELECT DISTINCT(p.name)
FROM
    movies m JOIN stars s JOIN people p
ON
    m.id = s.movie_id AND
    p.id = s.person_id
WHERE m.title LIKE "Toy Story%";
