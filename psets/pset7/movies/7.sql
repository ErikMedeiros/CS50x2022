-- https://cs50.harvard.edu/x/2022/psets/7/movies/

SELECT m.title, r.rating
FROM
    movies m JOIN ratings r
ON
    m.id = r.movie_id
WHERE m.year = 2010
ORDER BY r.rating DESC, m.title;
