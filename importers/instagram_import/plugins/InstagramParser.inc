<?php

/**
 * @file
 * Contains InstagramParser and related classes.
 */

/**
 * Class definition for Instagram Feed Parser.
 *
 * Parses Instagram feed.
 */
class InstagramParser extends FeedsParser {

  /**
   * Implements FeedsParser::parse().
   */
  public function parse(FeedsSource $source, FeedsFetcherResult $fetcher_result) {
    $feed = $fetcher_result->getRaw();
    $result = new FeedsParserResult();
    if (is_array($feed)) {
      foreach ($feed as $post) {

        $item = array();

        $item['global_id'] = $post->id;

        $item['user_name'] = $post->user->username;
        $item['full_name'] = $post->user->full_name;
        $item['user_id'] = $post->user->id;

        $item['item_id'] = $post->caption['id'];
        $item['item_link'] = $post->link;
        $item['created'] = $post->created_time;
        $item['image'] = $post->images['standard_resolution']['url'];
        $item['caption'] = $post->caption['text'];
        $item['comments'] = $post->comments['count'];
        $item['likes'] = $post->likes['count'];

        $result->items[] = $item;

      }
    }
    return $result;
  }

  /**
   * Return mapping sources.
   *
   * At a future point, we could expose data type information here,
   * storage systems like Data module could use this information to store
   * parsed data automatically in fields with a correct field type.
   */
  public function getMappingSources() {
    return array(
      'global_id' => array(
        'name' => t('Global ID'),
        'description' => t('Instagram item global ID.'),
      ),
      'user_name' => array(
        'name' => t('Username'),
        'description' => t('Instagram account name.'),
      ),
      'full_name' => array(
        'name' => t('Full name'),
        'description' => t('Instagram account full name.'),
      ),
      'user_id' => array(
        'name' => t('User ID'),
        'description' => t('Instagram account user ID.'),
      ),
      'item_id' => array(
        'name' => t('Item ID'),
        'description' => t('Instagram item ID.'),
      ),
      'item_link' => array(
        'name' => t('Item link'),
        'description' => t('Instagram item url.'),
      ),
      'created' => array(
        'name' => t('Created date'),
        'description' => t('Timestamp Instagram item was created.'),
      ),
      'image' => array(
        'name' => t('Photo'),
        'description' => t('Instagram photo.'),
      ),
      'caption' => array(
        'name' => t('Caption'),
        'description' => t('Instagram photo caption.'),
      ),
      'comments' => array(
        'name' => t('Comments'),
        'description' => t('Number of comments on Instagram item.'),
      ),
      'likes' => array(
        'name' => t('Likes'),
        'description' => t('Number of likes on Instagram item.'),
      ),
    ) + parent::getMappingSources();
  }
}
