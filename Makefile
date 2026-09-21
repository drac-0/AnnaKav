Dir = headerUndUtil/

.PHONY: annakav

annakav:
	gcc $(Dir)chprelated.c $(Dir)util.c $(Dir)sha.c annakat.c -o annakav 


