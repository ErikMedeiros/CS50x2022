-- https://cs50.harvard.edu/x/2022/psets/7/movies/

SELECT title, year
FROM movies
WHERE title LIKE "Harry Potter%"
ORDER BY year;
