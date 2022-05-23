-- https://cs50.harvard.edu/x/2022/labs/7/

SELECT AVG(s.energy) as average_energy
FROM songs s JOIN artists a
ON s.artist_id = a.id
WHERE a.name = "Drake";
