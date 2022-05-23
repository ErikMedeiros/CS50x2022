-- https://cs50.harvard.edu/x/2022/psets/7/movies/


SELECT COUNT(movie_id) AS count
FROM ratings
WHERE rating = 10.0;
