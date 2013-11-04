# Social

Drupal module suite for creating social entities and importing social items from web services.

The purpose behind this suite of modules is to create a proper approach to pulling social media content into your site in order that you might be able to use it while utilizing Drupal's content management and building tools. As a result, this module provides a way of importing data into Drupal data structures and then integrates it with Drupal rendering systems.

This module was the subject of a talk at Drupal Camp Michigan 2013: ["Social in your site, the right way"](https://speakerdeck.com/kevinchampion/social-in-your-drupal-site-the-right-way)

## Architecture

The social module creates a custom entity and entity type called 'social' and 'social type' respectively. By creating its own entity, social media content is able to be brought into the site in a custom format that does not muddle the node or any other entity interface in regards to the content administration and data structure. By including social types, this way of structuring the data is inherently extensible because it means we can simply create a social type for every social media service (ie. Twitter, Facebook, Instagram, etc.).

The data from these social services is imported using the [Feeds](https://drupal.org/project/feeds) module and by creating custom fetchers, parsers, and processors with the Feeds API in order to handle the specific needs for retrieving, munging, and storing the social data. This makes the approach extensible because it means that a single site can import from as many accounts on each social services as it wants.

## Social Services

The Social module comes with integration for the following services:

- Facebook
- Twitter (uses shortcut reliance on Twitter module, will be removed eventually)
- YouTube
- Instagram
- Pinterest

More social services can be added relatively easily due to the way this module suite is architected to be extensible.

TODO: Provide documentation on how a service can be added.

## Contents

This module suite contains the following modules:

- social: the base module, contains social entity, Feeds custom processor, views integration, and social admin
- facebook_import: importer module that provides the mechanics for fetching and parsing data from Facebook
- instagram_import: importer module that provides the mechanics for fetching and parsing data from Instagram
- pinterest_import: importer module that provides the mechanics for fetching and parsing data from Pinterest
- twitter_import: importer module that provides the mechanics for fetching and parsing data from Twitter
- youtube_import: importer module that provides the mechanics for fetching and parsing data from YouTube
- social_importer: example default configuration of social types and feeds importers
- social_blocks: example default block rendering to highlight social media items

TODO: Describe what all the components do and how/why things are structured as such.

## Installation

There are a lot of dependencies in order to install all of the included modules. Down the line there will be a drupal-org.make file to enable quick and easy setup using drush make.

TODO: Provide full install instructions

## Usage

Usage is a bit complicated and not exactly user-friendly. Don't expect to just install the module/s and intuitively understand what to do. The general steps are to:

1. navigate to /import
2. select an importer
3. enter the account information on the service you want to import from (this may require configuring account information on a settings form in order that the importer might be able to obtain an access token from the social service)
4. import
5. setup how you would like to render the data using views or another rendering technique

TODO: Provide more usage instruction, perhaps on a service-by-service basis
TODO: Provide better developer experience to make post-installation process easier and more intuitive (to help those who've just installed the modules know how to use them)




