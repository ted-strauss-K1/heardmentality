<div class="sort-wrapper">
  <span class="activity">SORT BY </span>&nbsp;
  <a class="active">All</a>
  | <a name="votes">Votes</a>
  | <a name="arguments">Arguments</a>
  | <a name="issues">Issues Added</a>
  <!--  | <a name=>References</a>-->
</div>

<div id="events_following">
  <?php
//  $p = array();
//  $p['uid'] = events_follower_uids();
//  $events = events_get($p);
//  print theme('events', $events);
  print theme('events', events_get(array(
    'q' => array(
      events_build_query(array('uid' => events_follower_uids(),)),
      events_build_query(array('type' => 'taxonomy',)),
    )
  )));
  ?>

</div>