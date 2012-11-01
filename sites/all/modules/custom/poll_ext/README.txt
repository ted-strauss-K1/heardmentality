Poll Vote History is DB trigger-tracked.

delimiter |
CREATE TRIGGER poll_vote_add AFTER INSERT ON poll_votes
FOR EACH ROW BEGIN
   INSERT INTO poll_votes_history SET
   date_voted = NOW(),
   status = 1,
   nid = NEW.nid,
   uid = NEW.uid,
   chorder = NEW.chorder, hostname = NEW.hostname;
END;

delimiter |
CREATE TRIGGER poll_vote_del AFTER DELETE ON poll_votes
FOR EACH ROW BEGIN
   UPDATE poll_votes_history SET status = 0 WHERE
   nid = OLD.nid AND
   uid = OLD.uid AND
   chorder = OLD.chorder AND
   hostname = OLD.hostname;
END;