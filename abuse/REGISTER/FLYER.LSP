;; Copyright 1995 Crack dot Com,  All Rights reserved
;; See licencing information for more details on usage rights

(def_char FLYER
  (funs (ai_fun flyer_ai)
	(damage_fun  flyer_damage)
	(constructor flyer_cons))

  (flags (hurtable T))
  (abilities (start_hp 20))
  (vars fire_delay burst_delay burst_total burst_wait burst_left 
	max_xvel   max_yvel    smoke_time fire_time)
  (fields ("fire_delay" "fire_delay")
	  ("burst_delay" "burst_delay")
	  ("burst_total" "burst_total")
	  ("max_xvel"    "max_xvel")
	  ("max_yvel"    "max_yvel")
	  ("hp" "hp")
	  ("aitype" "type")
	  ("aistate" "aistate"))
  
  (range 200 200)
  (states "art/flyer.spe"
	  (running (seq "ffly" 1 12))
	  (stopped (seq "unhurtable" 1 7))
	  (flinch_up  '("flinch" "flinch" "flinch"))
	  (turn_around (seq "ftrn" 1 6))))




(def_char GREEN_FLYER
  (funs (ai_fun flyer_ai)
	(damage_fun  flyer_damage)
	(constructor flyer_cons))

  (flags (hurtable T))
  (abilities (start_hp 20))
  (vars fire_delay burst_delay burst_total burst_wait burst_left 
	max_xvel   max_yvel    smoke_time fire_time)
  (fields ("fire_delay" "fire_delay")
	  ("burst_delay" "burst_delay")
	  ("burst_total" "burst_total")
	  ("max_xvel"    "max_xvel")
	  ("max_yvel"    "max_yvel")
	  ("hp" "hp")
	  ("aitype" "type")
	  ("aistate" "aistate"))
  
  (range 200 200)
  (states "art/flyer.spe"
	  (running (seq "gspe" 1 7))
	  (stopped (seq "gdrp" 1 12))
	  (flinch_up  '("ghurt" "ghurt" "ghurt"))
	  (turn_around (seq "gspn" 1 7))))



