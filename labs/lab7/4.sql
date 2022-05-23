-- https://cs50.harvard.edu/x/2022/labs/7/

SELECT name FROM songs
WHERE
    danceability > 0.75 AND
    energy > 0.75 AND
    valence > 0.75;
