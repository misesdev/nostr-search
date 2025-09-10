import { Suspense } from 'react';
import LoadingWeb from './loading';
import WebSearch from '@/components/search/WebSearch';
import { SearchParams } from '@/types/types';

const WebSearchPage = async ({ searchParams }: { searchParams: SearchParams }) => {

    const searchTerm = searchParams.searchTerm;

    return (
        <Suspense fallback={<LoadingWeb />}>
            <WebSearch searchTerm={searchTerm} />
        </Suspense>
    )
}

export default WebSearchPage
