<?php

/**
 * @file
 * Contains PinterestFeedParser and related classes.
 */

/**
 * Class definition for Pinterest Feed Parser.
 *
 * Parses Pinterst RSS feeds.
 */
class PinterestFeedParser extends FeedsSyndicationParser {

  /**
   * Implements FeedsParser::parse().
   */
  public function parse(FeedsSource $source, FeedsFetcherResult $fetcher_result) {
    feeds_include_library('common_syndication_parser.inc', 'common_syndication_parser');
    $feed = common_syndication_parser_parse($fetcher_result->getRaw());
    $result = new FeedsParserResult();
    $result->title = $feed['title'];
    $result->description = $feed['description'];
    $result->link = $feed['link'];
    if (is_array($feed['items'])) {
      foreach ($feed['items'] as $item) {
        // Extract ID from ID url.
        $pin_id = explode("/", $item['guid']);
        if (empty($pin_id[count($pin_id)-1])) {
          array_pop($pin_id);
        }
        $item['guid'] = end($pin_id);
        // Extract the image url from the description.
        $doc = new DOMDocument();
        @$doc->loadHTML($item['description']);
        $imgs = $doc->getElementsByTagName('img');
        foreach ($imgs as $img) {
          $item['image'] = $img->getAttribute('src');
        }
        // Extract textual description.
        $ps = $doc->getElementsByTagName('p');
        if (empty($ps->item(1)->hasChildNodes)) {
          $item['description'] = $ps->item(1)->nodeValue;
        }
        $item['username'] = $feed['title'];
        $item['account_link'] = $feed['link'];
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
      'username' => array(
        'name' => t('Username'),
        'description' => t('User account name.'),
      ),
      'account_link' => array(
        'name' => t('Account url'),
        'description' => t('Link to the Pinterest account.'),
      ),
      'title' => array(
        'name' => t('Title'),
        'description' => t('Title of the pin.'),
      ),
      'description' => array(
        'name' => t('Description'),
        'description' => t('Description of the pin.'),
      ),
      'author_name' => array(
        'name' => t('Author name'),
        'description' => t('Name of the pin\'s author.'),
      ),
      'timestamp' => array(
        'name' => t('Published date'),
        'description' => t('Published date as UNIX time GMT of the pin.'),
      ),
      'url' => array(
        'name' => t('Item URL (link)'),
        'description' => t('URL to the pin.'),
      ),
      'guid' => array(
        'name' => t('Item GUID'),
        'description' => t('Global Unique Identifier of the pin.'),
      ),
      'image' => array(
        'name' => t('Pin image'),
        'description' => t('Url to the pin image.'),
      ),
      'tags' => array(
        'name' => t('Categories'),
        'description' => t('An array of categories that have been assigned to the pin.'),
      ),
      'geolocations' => array(
        'name' => t('Geo Locations'),
        'description' => t('An array of geographic locations with a name and a position.'),
      ),
    ) + parent::getMappingSources();
  }
}
