" Some helpful vim functions to edit fasterer
" Change each 2 octets to 'XX' ===> '$XX '
fun! Xxdtoa65()
	let i=0
	while i<16
		norm i$
		norm llli, 
		norm l
		let i+=1
	endwhile
endfun

" Add commas to end of each 'word' x 15
fun! Addcommas()
	let i=0
	while i<15
		norm Ea,
		let i+=1
	endwhile
endfun
